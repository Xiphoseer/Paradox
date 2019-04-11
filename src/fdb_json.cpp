#include "fdb_json.hpp"

#include <assembly/fdb_query.hpp>
#include <iostream>

#include "json.hpp"


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
      std::cout << "## " << it->first << std::endl;
      std::cout << "> " << it->second.description << std::endl;

      const table_t& table = it->second.table;

      std::cout << "SLOTS: " << table.slots.size() << std::endl;
      std::cout << std::endl;

      auto t_it = assembly::database::query::for_table(table);
      while (t_it) {
        auto row = *t_it;

        json j_ref_elem;
        j_ref_elem["id"] = row.fields.at(0);

        ++t_it;
      }
    }
  }

  output_t::output_t(const schema_t& schema) : schema(schema)
  {

  }
}
