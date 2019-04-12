#include "fdb_json.hpp"

#include <assembly/fdb_query.hpp>
#include <iostream>

#include "json.hpp"
#include "store.hpp"


using namespace nlohmann;

namespace paradox::fdb
{

  output_error::output_error(const std::string& what)
  : std::runtime_error(what) {}

  ref_output_t::ref_output_t(const std::string& name, const std::string& description)
  : name(name), description(description)
  {

  }

  void index_output_t::ref_id_column()
  {
    this->fields.emplace(this->table.columns.at(0).name, [](const row_t& r){return r.fields.at(0);});
  }

  void index_output_t::ref_column(const std::string& name)
  {
    this->fields.emplace(name, this->table.column_sel(name));
  }

  void index_output_t::ref_columns(const std::vector<std::string> fields)
  {
    for (const std::string& field : fields) {
      this->ref_column(field);
    }
  }

  index_output_t::index_output_t(ref_output_t& ref, const table_t& table)
  : ref(ref), table(table)
  {

  }

  index_output_t& field_output_t::add_ref(ref_output_t& ref_out)
  {
    this->refs.emplace_back(index_output_t{ref_out, this->table});
    index_output_t& index_out = this->refs.back();
    return index_out;
  }

  field_output_t::field_output_t(const column_t& column, int index, const std::string& name, const table_t& table)
  : index(index), column(column), name(name), table(table)
  {

  }

  field_output_t& table_output_t::add_field(const std::string& field)
  {
    auto db_col = this->table.column_def(field);

    field_output_t& field_out = this->fields.emplace(field, field_output_t{db_col.second, db_col.first, field, this->table}).first->second;
    return field_out;
  }

  table_output_t::table_output_t(const table_t& table) : table(table)
  {

  }

  table_output_t& output_t::add_table(const std::string& table, const std::string& description)
  {
    const table_t& db_table = this->schema.at(table);

    table_output_t& table_out = this->tables.emplace(table, table_output_t{db_table}).first->second;
    table_out.name = table;
    table_out.description = description;
    return table_out;
  }

  ref_output_t& output_t::add_ref(const std::string& ref, const std::string& description)
  {
    ref_output_t& ref_out = this->refs.emplace(ref, ref_output_t{ref, description}).first->second;
    return ref_out;
  }

  //! Configure the output
  void output_t::configure(const json& j_config)
  {
    const json& j_refs_config = j_config["refs"];
    const json& j_db_config = j_config["database"];
    const json& j_db_tables_config = j_db_config["tables"];

    std::map<std::string, ref_output_t&> refs;

    for (auto it = j_refs_config.begin(); it != j_refs_config.end(); ++it) {
      const std::string& ref_name = it.key();
      const json& j_ref_config = it.value();
      const std::string& ref_desc = j_ref_config.value("description", "");
      if (ref_desc.empty()) {
        throw new output_error("Missing description for ref `" + ref_name + "`");
      }

      ref_output_t& ref = this->add_ref(ref_name, ref_desc);
      refs.emplace(ref_name, ref);
    }

    for (auto it = j_db_tables_config.begin(); it != j_db_tables_config.end(); ++it) {
      const std::string& table_name = it.key();
      std::cout << "## " << table_name << std::endl;

      const json& j_table_config = it.value();
      const std::string& table_desc = j_table_config.value("description", "");
      if (table_desc.empty()) {
        throw new output_error("Missing description for table `" + table_name + "`");
      }
      const json& j_table_fields_config = j_table_config.value("fields", json());

      table_output_t& table_o = this->add_table(table_name, table_desc);

      for (auto f_it = j_table_fields_config.begin(); f_it != j_table_fields_config.end(); ++f_it) {
        const std::string& field_name = f_it.key();
        const json& j_table_field_config = f_it.value();
        const json& j_table_field_refs_config = j_table_field_config["refs"];

        field_output_t& field_o = table_o.add_field(field_name);

        for (auto r_it = j_table_field_refs_config.begin(); r_it != j_table_field_refs_config.end(); ++r_it) {
          const std::string& ref_name = r_it.key();
          const json& j_table_field_ref_config = r_it.value();
          const json& j_table_field_ref_columns_config = j_table_field_ref_config["ref_columns"];

          ref_output_t& ref = refs.at(ref_name);
          index_output_t& index_o = field_o.add_ref(ref);

          for (auto c_it = j_table_field_ref_columns_config.begin(); c_it != j_table_field_ref_columns_config.end(); ++c_it) {

            const std::string& column_name = *c_it;

            index_o.ref_column(column_name);
          }
        }
      }
    }
  }

  //! Configure the output
  void output_t::configure_from_file(const std::string& path)
  {
    std::ifstream infile(path);
    json j_config;
    infile >> j_config;
    infile.close();

    this->configure(j_config);
  }

  void output_t::execute()
  {
    json j_refs;

    std::cout << "# Output" << std::endl;
    std::cout << std::endl;
    for (auto it = this->tables.begin(); it != this->tables.end(); ++it) {

      const std::string& table_name = it->first;
      const table_output_t& t_out = it->second;
      const table_t& table = t_out.table;

      std::cout << "## " << table_name << std::endl;
      std::cout << "> " << t_out.description << std::endl;

      auto t_it = assembly::database::query::for_table(table);
      while (t_it) {
        auto row = *t_it;

        field_t id_field = row.fields.at(0);

        for(auto f_it = t_out.fields.begin(); f_it != t_out.fields.end(); ++f_it) {
          const std::string& field_name = f_it->first;

          const field_output_t& f_out = f_it->second;
          const field_t& field = row.fields.at(f_out.index);

          for (auto i_it = f_out.refs.begin(); i_it != f_out.refs.end(); ++i_it) {
            const index_output_t& i_out = *i_it;
            const ref_output_t& r_out = i_out.ref;
            const std::string& ref_name = r_out.name;

            json j_ref_elem;
            if (i_out.fields.size() > 0) {
              for (auto m_it = i_out.fields.begin(); m_it != i_out.fields.end(); ++m_it) {
                j_ref_elem[m_it->first] = m_it->second(row);
              }
            } else {
              j_ref_elem["id"] = id_field;
            }

            j_refs[ref_name][field.to_string()][table_name][field_name] += j_ref_elem;
          }
        }

        ++t_it;
      }
    }

    paradox::data::store_json_t store;
    const std::string& path_refs = "refs/";
    std::cout << "# References" << std::endl;

    for (auto jr_it = j_refs.begin(); jr_it != j_refs.end(); ++jr_it) {
      const std::string& ref_name = jr_it.key();
      std::cout << "## " << ref_name << std::endl;

      const json& j_ref_data = jr_it.value();
      const std::string& path_ref = path_refs + ref_name + "/";

      for (auto jd_it = j_ref_data.begin(); jd_it != j_ref_data.end(); ++jd_it) {
        const std::string key = jd_it.key();

        const json& j_ref_key = jd_it.value();
        const std::string& path_ref_key = path_ref + key;

        store.save(j_ref_key, path_ref_key);
      }
    }
  }

  output_t::output_t(const schema_t& schema) : schema(schema)
  {

  }
}
