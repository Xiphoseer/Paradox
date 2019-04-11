#pragma once

#include <assembly/database.hpp>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>


namespace paradox::fdb {

  typedef assembly::database::schema schema_t;
  typedef assembly::database::table table_t;
  typedef assembly::database::column column_t;
  typedef assembly::database::field field_t;

  class output_error : std::runtime_error {

  };

  //! Represents a key for the database, e.g. LOT
  struct ref_output_t
  {
    //! The name of this ref
    const std::string& name;

    //! A description for this ref
    const std::string& description;

    //! Constructor
    ref_output_t(const std::string& name, const std::string& description);
  };

  struct index_output_t
  {
    ref_output_t& ref;

    //! Constructor
    index_output_t(ref_output_t& ref);
  };

  struct field_output_t
  {
    //! The name of the field
    const std::string& name;

    //! The column
    const column_t& column;

    //! The column index
    int index;

    //! All indices to which this field exports
    std::vector<index_output_t> refs;

    //! Adds an index serialization struct
    index_output_t& add_ref(ref_output_t& ref);

    //! Constructor
    field_output_t(const column_t& column, int index, const std::string& name);
  };

  struct table_output_t
  {
    //! The name of this table
    std::string name;

    //! The description for this table
    std::string description;

    //! The reference to the table struct
    const table_t& table;

    //! The map to the output fields
    std::map<std::string, field_output_t> fields;

    //! The function to add a field output
    field_output_t& add_field(const std::string& field);

    //! Constructor
    table_output_t(const table_t& table);
  };

  struct output_t
  {
    //! The schema for this output
    const schema_t& schema;

    //! The map of table outputs
    std::map<std::string, table_output_t> tables;

    //! The map of references
    std::map<std::string, ref_output_t> refs;

    //! Adds a table to be serialized
    table_output_t& add_table(const std::string& table, const std::string& description);

    //! Adds a reference to this output
    ref_output_t& add_ref(const std::string& ref, const std::string& description);

    //! Executes the export
    void execute();

    //! Create an output for the specified schema
    output_t(const assembly::database::schema& schema);
  };
}
