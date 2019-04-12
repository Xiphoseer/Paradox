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
  typedef assembly::database::row row_t;

  class output_error : std::runtime_error {
  public:
    output_error(const std::string& what);
  };

  //! Represents a key for the database, e.g. LOT
  struct ref_output_t
  {
    //! The name of this ref
    const std::string name;

    //! A description for this ref
    const std::string description;

    //! Constructor
    ref_output_t(const std::string& name, const std::string& description);
  };

  struct index_output_t
  {
    //! Reference to the REF structure
    ref_output_t& ref;

    //! The table
    const table_t& table;

    //! Information on which fields get ref'd
    std::map<std::string, std::function<const field_t&(const row_t&)>> fields;

    //! Add the ID column
    void ref_id_column();
    void ref_column(const std::string& name);
    void ref_columns(const std::vector<std::string> fields);

    //! Constructor
    index_output_t(ref_output_t& ref, const table_t& table);
  };

  struct field_output_t
  {
    //! The name of the field
    const std::string name;

    //! The column
    const column_t& column;

    //! The table
    const table_t& table;

    //! The column index
    int index;

    //! All indices to which this field exports
    std::vector<index_output_t> refs;

    //! Adds an index serialization struct
    index_output_t& add_ref(ref_output_t& ref);

    //! Constructor
    field_output_t(const column_t& column, int index, const std::string& name, const table_t& table);
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

    //! Configure the output
    void configure(const nlohmann::json& config);

    //! Configure the output
    void configure_from_file(const std::string& path);

    //! Create an output for the specified schema
    output_t(const assembly::database::schema& schema);
  };
}
