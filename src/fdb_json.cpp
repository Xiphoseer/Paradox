#include "fdb_json.hpp"

#include <assembly/fdb_query.hpp>
#include <iostream>

#include "json.hpp"
#include "store.hpp"


using namespace nlohmann;

namespace paradox::fdb
{

  ref_output_t::ref_output_t(const std::string& name, const std::string& description)
  : name(name), description(description)
  {

  }

  index_output_t::index_output_t(ref_output_t& ref) : ref(ref)
  {

  }

  index_output_t& field_output_t::add_ref(ref_output_t& ref_out)
  {
    this->refs.emplace_back(index_output_t{ref_out});
    index_output_t& index_out = this->refs.back();
    return index_out;
  }

  field_output_t::field_output_t(const column_t& column, int index, const std::string& name)
  : index(index), column(column), name(name)
  {

  }

  field_output_t& table_output_t::add_field(const std::string& field)
  {
    auto db_col = this->table.column_def(field);

    field_output_t& field_out = this->fields.emplace(field, field_output_t{db_col.second, db_col.first, field}).first->second;
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
      std::cout << "SLOTS: " << table.slots.size() << std::endl;
      std::cout << std::endl;

      auto t_it = assembly::database::query::for_table(table);
      while (t_it) {
        auto row = *t_it;

        field_t id_field = row.fields.at(0);

        json j_ref_elem;
        j_ref_elem["id"] = id_field;

        for(auto f_it = t_out.fields.begin(); f_it != t_out.fields.end(); ++f_it) {
          const std::string& field_name = f_it->first;

          const field_output_t& f_out = f_it->second;
          const field_t& field = row.fields.at(f_out.index);

          for (auto i_it = f_out.refs.begin(); i_it != f_out.refs.end(); ++i_it) {
            const index_output_t& i_out = *i_it;
            const ref_output_t& r_out = i_out.ref;
            const std::string& ref_name = r_out.name;

            j_refs[ref_name][field.to_string()][table_name][field_name] += j_ref_elem;
          }
        }

        ++t_it;
      }
    }

    paradox::data::store_json_t store;
    const std::string& path_refs = "refs/";
    std::cout << "# REFS" << std::endl;

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
