#include "fdb_cli.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>

#include <Magick++.h>
#include <nlohmann/json.hpp>

#include <assembly/utf.hpp>
#include <assembly/filesystem.hpp>
#include <assembly/database.hpp>
#include <assembly/fdb_io.hpp>
#include <assembly/fdb_query.hpp>
#include <assembly/stringutil.hpp>
#include <assembly/cli.hpp>
#include <assembly/functional.hpp>

using namespace nlohmann;

cli::opt_t fdb_options[] =
{
    { "read",           &fdb_read,          "Reads a fdb file" },
    { "behaviors",      &fdb_behaviors,     "Writes all behavior parameters" },
    //{ "convert",        &fdb_convert,       "Convert an image to another format" },
    { "header",         &fdb_header,        "Generate c++ files for a FDB" },
    /*{ "docs-table",     &fdb_docs_table,    "Generate a single reST page for a FDB table" },
    { "docs-tables",    &fdb_docs_tables,   "Generate a folder of reST pages for a FDB table" },
    { "all-tables",     &fdb_all_tables,    "Generate a reST list of all tables" },*/
    { "help",           &help_fdb,          "Show this help" },
    { 0, 0, 0 }
};

const int lens[] = {4,15,4,15,50,3,20,4,30};
const char* types[] = {"NOTHING", "INTEGER", "UNKNOWN1", "FLOAT", "TEXT", "BOOLEAN", "BIGINT", "UNKNOWN2", "VARCHAR" };

int main_fdb(int argc, char** argv)
{
    int optind = 1;

    if (argc <= optind) {
        std::cout << "Usage: fdb <subcommand> ..." << std::endl;
        return 1;
    }

    return cli::call("DatabaseCLI", fdb_options, argv[optind], argc - optind, argv + optind);
}

int help_fdb (int argc, char** argv)
{
    cli::help("DatabaseCLI", fdb_options, "FileDataBase manipulation tool");
}

void print_state (const std::ios& stream)
{
    std::cout << " good()=" << stream.good();
    std::cout << " eof()=" << stream.eof();
    std::cout << " fail()=" << stream.fail();
    std::cout << " bad()=" << stream.bad();
    std::cout << std::endl;
}

void print(int i)
{
    std::cout << i << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, const assembly::database::field& f)
{
    switch(f.type)
    {
        case assembly::database::value_type::BOOLEAN:
        case assembly::database::value_type::INTEGER:  ostr << f.int_val; break;
        case assembly::database::value_type::FLOAT:    ostr << f.flt_val; break;
        case assembly::database::value_type::BIGINT:   ostr << f.i64_val; break;
        case assembly::database::value_type::VARCHAR:
        case assembly::database::value_type::TEXT: ostr << f.str_val; break;
    }
    return ostr;
}

const utf::iconv_to_utf8 fromLatin1("ISO-8859-1");

const json fdb_to_json(const assembly::database::field& f)
{
    switch(f.type)
    {
        case assembly::database::value_type::BOOLEAN: return json(f.int_val != 0);
        case assembly::database::value_type::INTEGER: return json(f.int_val);
        case assembly::database::value_type::FLOAT:   return json(f.flt_val);
        case assembly::database::value_type::BIGINT:  return json(f.i64_val);
        case assembly::database::value_type::VARCHAR:
        case assembly::database::value_type::TEXT: return json(fromLatin1(f.str_val));
    }
    return json();
}

std::string to_json_path(const std::string& path)
{
    return "lu-json/" + path + ".json";
}

std::string to_xml_path(const std::string& path)
{
    return "lu-xml/" + path + ".xml";
}

std::ofstream make_json_file(const std::string& path)
{
    std::string json_file = to_json_path(path);
    fs::ensure_dir_exists(json_file);
    return std::ofstream(json_file);
}

std::ofstream make_xml_file(const std::string& path)
{
    std::string xml_file = to_xml_path(path);
    fs::ensure_dir_exists(xml_file);
    return std::ofstream(xml_file);
}

std::string get_unpaged_suffix(int id)
{
    return "/" + std::to_string(id);
}

std::string get_paged_suffix(int id)
{
    int page = id / 256;
    return "/" + std::to_string(page) + "/" + std::to_string(id);
}

std::string get_dblpaged_suffix(int id)
{
    int page_a = id / 256;
    int page_b = page_a / 256;
    return "/" + std::to_string(page_a) + "/" + std::to_string(page_b) + "/" + std::to_string(id);
}

/*! \brief Store a database table to disc
 *
 */
void store_table
(
    const assembly::database::schema& schema, std::string path_tables,
    std::string table_name, std::function<std::string(int)> pager
){
    std::cout << "=== " << table_name << " ===" << std::endl;
    const assembly::database::table& table = schema.at(table_name);

    // Change "MinifigDecals_Mouths" to "MinifigDecals/Mouths" on disc
    std::string path_name = replace_all_copy(table_name, "_", "/");
    std::string path_tables_table = path_tables + "/" + path_name;
    std::string index_tables_table = path_tables_table + "/index";

    auto it = assembly::database::query::for_table(table);
    json j_index;

    while (it)
    {
        const assembly::database::row& r = *it;
        json j_elem;

        int id = r.fields.at(0).int_val;
        std::string item_tables_table = path_tables_table + pager(id);

        json j_index_elem;
        j_index_elem["id"] = id;
        j_index_elem["_links"]["self"]["href"] = "/" + to_json_path(item_tables_table);
        j_index["_embedded"][table_name] += j_index_elem;

        for (int i = 0; i < table.columns.size(); i++)
        {
          try
          {
            j_elem[table.columns.at(i).name] = fdb_to_json(r.fields.at(i));
          }
          catch (std::runtime_error err)
          {
            std::cerr << "Error '" << err.what() << " while processing PK " << id << ", COL " << i << std::endl;
          }
        }

        std::ofstream table_elem = make_json_file(item_tables_table);
        try
        {
          table_elem << std::setw(2) << j_elem << std::endl;
        }
        catch (nlohmann::detail::type_error err)
        {
            // TODO: Investigate why some strings are invalid UTF-8
            std::cerr << "Error '" << err.what() << " while processing PK " << id << std::endl;
        }
        table_elem.close();

        ++it;
    }

    std::ofstream index_table = make_json_file(index_tables_table);
    index_table << std::setw(2) << j_index << std::endl;
    index_table.close();
}

void store_many_table(
    const assembly::database::schema& schema, const std::string& path_tables,
    const std::string& name, const std::string& elems_name
){
    // LootMatrix
    // -LootMatrixIndex
    // elements

    std::cout << "=== " << name << " ===" << std::endl;
    const assembly::database::table& tbl = schema.at(name);
    std::string path_tables_tbl = path_tables + "/" + name;

    int i = 0;
    int max = tbl.slots.size();

    while (i < max)
    {
        json j_elem;
        j_elem[tbl.columns.at(0).name] = i;
        assembly::database::query::int_eq checkID(i);

        bool found = false;

        for (const assembly::database::row& r : tbl.at(i).rows)
        {
            found = true;
            json j_elem_part;
            assembly::database::field id_field = r.fields.at(0);
            int id = id_field.int_val;

            if (id > max) max = id + 1;

            if (checkID(id_field))
            {
                for (int i = 1; i < tbl.columns.size(); i++)
                {
                    j_elem_part[tbl.columns.at(i).name] = fdb_to_json(r.fields.at(i));
                }
            }

            j_elem[elems_name] += j_elem_part;
        }

        if (found)
        {
            int page = i / 256;

            std::string item_tables_tbl = path_tables_tbl
                + "/" + std::to_string(page) + "/" + std::to_string(i);
            std::ofstream tbl_elem = make_json_file(item_tables_tbl);
            tbl_elem << std::setw(2) << j_elem << std::endl;
            tbl_elem.close();
        }

        i++;
    }
}

void store_unpaged_table(const assembly::database::schema& schema, std::string path_tables, std::string table_name)
{
    store_table(schema, path_tables, table_name, get_unpaged_suffix);
}

void store_paged_table(const assembly::database::schema& schema, std::string path_tables, std::string table_name)
{
    store_table(schema, path_tables, table_name, get_paged_suffix);
}

void store_single_table(const assembly::database::schema& schema, const std::string path_tables, const std::string& table_name)
{
    std::cout << "=== " << table_name << " ===" << std::endl;

    const assembly::database::table& single = schema.at(table_name);
    std::string path_tables_single = path_tables + "/" + table_name;
    std::string index_tables_single = path_tables_single + "/index";

    json j_single_index;
    j_single_index["_links"]["self"]["href"] =  "/" + to_json_path(index_tables_single);
    j_single_index["_embedded"][table_name] = json::array();

    auto it = assembly::database::query::for_table(single);

    while (it)
    {
        const assembly::database::row& r = *it;
        json j_elem;

        for (int i = 0; i < single.columns.size(); i++)
        {
            j_elem[single.columns.at(i).name] = fdb_to_json(r.fields.at(i));
        }

        j_single_index["_embedded"][table_name] += j_elem;

        ++it;
    }

    std::ofstream single_index = make_json_file(index_tables_single);
    single_index << std::setw(2) << j_single_index << std::endl;
    single_index.close();
}

//! Stores the missions grouped by their types
int store_missions_tables(const assembly::database::schema& schema)
{
  std::cout << "=== Mission Index ===" << std::endl;

  const auto tbl = schema.at("Missions");
  auto it = assembly::database::query::for_table(tbl);

  auto id_sel = tbl.column_sel("id");
  auto defined_type_sel = tbl.column_sel("defined_type");
  auto defined_subtype_sel = tbl.column_sel("defined_subtype");

  json j_missions;

  while (it) {
    auto row = *it;
    auto id = id_sel(row).int_val;

    auto defined_type = defined_type_sel(row).get_str("");
    auto defined_subtype = defined_subtype_sel(row).get_str("");

    j_missions[defined_type][defined_subtype] += id;

    ++it;
  }

  const std::string path_missions = "tables/Missions";
  const std::string index_missions = path_missions + "/groupBy/type";
  std::ofstream missions = make_json_file(index_missions);

  missions << std::setw(2) << j_missions << std::endl;
  missions.close();
}

//! Stores the tables for the zones
void store_zone_tables(
  const assembly::database::schema& schema,
  const std::string& path_tables,
  const std::string& path_zones)
{
  std::cout << "=== ZoneTable ===" << std::endl;

  const assembly::database::table& tbl = schema.at("ZoneTable");

  std::string path_tables_zones = path_tables + "/ZoneTable";
  std::string index_tables_zones = path_tables_zones + "/index";

  std::ofstream zone_index = make_json_file(index_tables_zones);

  json j_index;
  j_index["_links"]["self"]["href"] =  "/" + to_json_path(index_tables_zones);
  j_index["_embedded"]["ZoneTable"] = json::array();

  auto id_sel = tbl.column_sel("zoneID");
  auto file_sel = tbl.column_sel("zoneName");
  auto display_sel = tbl.column_sel("DisplayDescription");

  auto removed_filter = assembly::database::query::like("%__removed");

  assembly::database::query::const_iterator it = assembly::database::query::for_table(tbl);

  while (it)
  {
    const assembly::database::row& r = *it;

    const assembly::database::field& file = file_sel(r);
    const assembly::database::field& display = display_sel(r);

    if (!removed_filter(file) && display.type != assembly::database::value_type::NOTHING)
    {
      const assembly::database::field& zone_id = id_sel(r);

      std::string item_tables_zones = path_tables_zones + "/" + std::to_string(zone_id.int_val);
      std::string item_zones = path_zones + "/" + std::to_string(zone_id.int_val);
      std::ofstream zone = make_json_file(item_tables_zones);

      json j_zone;
      j_zone["_links"]["self"]["href"] = "/" + to_json_path(item_tables_zones);

      for (int i = 0; i < tbl.columns.size(); i++)
      {
        j_zone[tbl.columns.at(i).name] = fdb_to_json(r.fields.at(i));
      }

      zone << std::setw(2) << j_zone << std::endl;
      zone.close();

      json j_index_element;
      j_index_element["_links"]["self"]["href"] = "/" + to_json_path(item_tables_zones);
      j_index_element["_links"]["level"]["href"] = "/" + to_json_path(item_zones);

      j_index_element["zoneID"] = zone_id.int_val;
      j_index_element["zoneName"] = file.str_val;
      j_index_element["DisplayDescription"] = display.str_val;

      j_index["_embedded"]["ZoneTable"] += j_index_element;
    }
    ++it;
  }

  zone_index << std::setw(2) << j_index << std::endl;
  zone_index.close();
}

//! Stores the tables for the behaviors
void store_behavior_tables(
  const assembly::database::schema& schema,
  const std::string& path_behaviors)
{
  std::cout << "=== Behaviors ===" << std::endl;

  int max_key = 65536;
  int behaviorID = 0;
  int page_index = 0;
  int page_size = 1024;

  const assembly::database::table& behavior_params = schema.at("BehaviorParameter");
  const assembly::database::table& behavior_template = schema.at("BehaviorTemplate");

  auto behavior_template_behavior_id_sel = behavior_template.column_sel("behaviorID");
  auto behavior_template_template_id_sel = behavior_template.column_sel("templateID");
  auto behavior_template_effect_id_sel = behavior_template.column_sel("effectID");
  auto behavior_template_effect_handle_sel = behavior_template.column_sel("effectHandle");

  auto behavior_params_behavior_id_sel = behavior_params.column_sel("behaviorID");
  auto behavior_params_parameter_id_sel = behavior_params.column_sel("parameterID");
  auto behavior_params_value_sel = behavior_params.column_sel("value");

  std::string index_behaviors = path_behaviors + "/index";

  std::string current_folder = path_behaviors + "/0";
  std::string current_page = current_folder + "/index";

  json j_behavior_index;
  j_behavior_index["_links"]["self"]["href"] = "/" + to_json_path(index_behaviors);
  j_behavior_index["_links"]["first"]["href"] = "/" + to_json_path(current_page);

  json j_behavior_page;

  while (behaviorID < max_key)
  {
      bool found = false;
      int slot = behaviorID % 35536;

      int new_page_index = behaviorID / 1024;
      if (new_page_index > page_index)
      {
          current_folder = path_behaviors + "/" + std::to_string(new_page_index);
          std::string next_page = current_folder + "/index";

          j_behavior_page["_links"]["next"]["href"] = "/" + to_json_path(next_page);
          j_behavior_page["_links"]["self"]["href"] = "/" + to_json_path(current_page);

          json j_index_entry;
          j_index_entry["_links"]["self"]["href"] = "/" + to_json_path(current_page);

          j_behavior_index["_embedded"]["pages"] += j_index_entry;

          std::ofstream page_path = make_json_file(current_page);
          page_path << std::setw(2) << j_behavior_page << std::endl;
          page_path.close();

          j_behavior_page = json();
          j_behavior_page["_links"]["prev"]["href"] = "/" + to_json_path(current_page);

          current_page = next_page;
          page_index = new_page_index;
      }

      std::string current = current_folder + "/" + std::to_string(behaviorID);

      json j_behavior;
      assembly::database::query::int_eq checkID(behaviorID);

      const assembly::database::slot& params_slot = behavior_params.slots.at(slot);
      const assembly::database::slot& template_slot = behavior_template.slots.at(slot);

      for (const assembly::database::row& row : template_slot.rows)
      {
          auto id_field = behavior_template_behavior_id_sel(row);
          if (id_field.type == assembly::database::value_type::INTEGER && id_field.int_val > max_key)
          {
              max_key = id_field.int_val + 1;
          }

          if (checkID(id_field))
          {
              j_behavior["_links"]["self"]["href"] = "/" + to_json_path(current);

              j_behavior["behaviorID"] = fdb_to_json(id_field);
              j_behavior["templateID"] = fdb_to_json(behavior_template_template_id_sel(row));
              j_behavior["effectID"] = fdb_to_json(behavior_template_effect_id_sel(row));
              j_behavior["effectHandle"] = fdb_to_json(behavior_template_effect_handle_sel(row));

              j_behavior_page["_embedded"]["behaviors"] += j_behavior;
          }
          found = true;
      }

      for (const assembly::database::row& row : params_slot.rows)
      {
          auto id_field = behavior_params_behavior_id_sel(row);
          if (id_field.type == assembly::database::value_type::INTEGER && id_field.int_val > max_key)
          {
              max_key = id_field.int_val + 1;
          }

          if (checkID(id_field))
          {
              auto key_field = behavior_params_parameter_id_sel(row);
              if (key_field.type == assembly::database::value_type::TEXT || key_field.type == assembly::database::value_type::VARCHAR)
              {
                  std::string key = key_field.str_val;
                  j_behavior["parameters"][key] = fdb_to_json(behavior_params_value_sel(row));
              }
          }
      }

      if (found)
      {
          std::ofstream behavior_file = make_json_file(current);
          behavior_file << std::setw(2) << j_behavior << std::endl;
      }

      behaviorID++;
  }

  j_behavior_page["_links"]["self"]["href"] = "/" + to_json_path(current_page);

  json j_index_entry;
  j_index_entry["_links"]["self"]["href"] = "/" + to_json_path(current_page);

  j_behavior_index["_embedded"]["pages"] += j_index_entry;
  j_behavior_index["_links"]["last"]["href"] = "/" + to_json_path(current_page);

  std::ofstream page_path = make_json_file(current_page);
  page_path << std::setw(2) << j_behavior_page << std::endl;
  page_path.close();

  std::ofstream index_file = make_json_file(index_behaviors);
  index_file << std::setw(2) << j_behavior_index << std::endl;
  index_file.close();
}

void store_loot_tables(
  const assembly::database::schema& schema,
  const std::string path_tables)
{
  std::cout << "=== LootTable ===" << std::endl;
  const assembly::database::table& loot_table = schema.at("LootTable");
  std::string path_tables_loot = path_tables + "/LootTable";
  std::string path_tables_loot__itemid = path_tables_loot + "/groupBy/itemid";
  std::string path_tables_loot__index = path_tables_loot + "/groupBy/LootTableIndex";

  json j_loot_table;

  for (const assembly::database::slot& slot: loot_table.slots)
  {
    json j_elem;

    for (const assembly::database::row& r : slot.rows)
    {
      json j_elem_part;

      assembly::database::field id_field = r.fields.at(0);
      assembly::database::field lti_field = r.fields.at(1);

      int id = id_field.int_val;
      int lti = lti_field.int_val;

      for (int i = 2; i < loot_table.columns.size(); i++)
      {
        j_elem_part[loot_table.columns.at(i).name] = fdb_to_json(r.fields.at(i));
      }

      json j_item_part(j_elem_part);
      j_item_part.emplace("LootTableIndex", lti);

      json j_loot_part(j_elem_part);
      j_loot_part.emplace("itemid", id);

      j_elem[std::to_string(id)]["elements"] += j_item_part;
      j_loot_table[std::to_string(lti)]["elements"] += j_loot_part;
    }

    for (json::iterator it = j_elem.begin(); it != j_elem.end(); ++it)
    {
      int i = std::stoi(it.key());
      int page = i / 256;
      it.value()["itemid"] = i;

      std::string item_tables_loot_table = path_tables_loot__itemid
        + "/" + std::to_string(page) + "/" + std::to_string(i);
      std::ofstream loot_table_elem = make_json_file(item_tables_loot_table);
      loot_table_elem << std::setw(2) << it.value() << std::endl;
      loot_table_elem.close();
    }
  }

  for (json::iterator it = j_loot_table.begin(); it != j_loot_table.end(); ++it)
  {
    int i = std::stoi(it.key());
    int page = i / 256;
    it.value()["LootTableIndex"] = i;

    std::string item_tables_loot_table = path_tables_loot__index
        + "/" + std::to_string(page) + "/" + std::to_string(i);
    std::ofstream loot_table_elem = make_json_file(item_tables_loot_table);
    loot_table_elem << std::setw(2) << it.value() << std::endl;
    loot_table_elem.close();
  }

  j_loot_table.clear();
}

void store_object_tables(
  const assembly::database::schema& schema,
  const std::string& path_objects)
{
  std::cout << "=== Objects ===" << std::endl;
  const assembly::database::table& objects = schema.at("Objects"); // 16384
  const assembly::database::table& components = schema.at("ComponentsRegistry"); // 32768
  const assembly::database::table& oskill = schema.at("ObjectSkills"); // 4096
  const assembly::database::table& mIcon = schema.at("mapIcon"); // 4096

  auto objects_id_sel = objects.column_sel("id");
  auto objects_type_sel = objects.column_sel("type");
  auto objects_name_sel = objects.column_sel("name");

  auto it = assembly::database::query::for_table(objects);
  json j_objects_by_type;

  while (it)
  {
    json j_object;
    const assembly::database::row& r = *it;

    int objID = objects_id_sel(r).int_val;
    assembly::database::query::int_eq checkID(objID);

    // Load all fields
    for (int i = 0; i < objects.columns.size(); i++)
    {
      try
      {
        j_object[objects.columns.at(i).name] = fdb_to_json(r.fields.at(i));
      }
      catch (std::runtime_error err)
      {
        std::cerr << "Error while processing PK " << objID << ", COL " << i << std::endl
                  << "  what(): " << err.what() << std::endl;
      }
    }

    // Store byType
    std::string type = fromLatin1(objects_type_sel(r).get_str(""));
    std::string name = fromLatin1(objects_name_sel(r).get_str(""));
    json j_object_ref;
    j_object_ref["id"] = objID;
    j_object_ref["name"] = name;
    j_objects_by_type[type] += j_object_ref;

    for (const assembly::database::row& row: components.at(objID).rows)
    {
      auto id_field = row.fields.at(0);
      if (checkID(id_field))
      {
        j_object["components"][std::to_string(row.fields.at(1).int_val)] = row.fields.at(2).int_val;
      }
    }

    for (const assembly::database::row& row: oskill.at(objID).rows)
    {
      auto id_field = row.fields.at(0);
      if (checkID(id_field))
      {
        json j_skill;
        j_skill["skillID"] = row.fields.at(1).int_val;
        j_skill["castOnType"] = row.fields.at(2).int_val;
        j_skill["AICombatWeight"] = row.fields.at(3).int_val;
        j_object["skills"] += j_skill;
      }
    }

    for (const assembly::database::row& row: mIcon.at(objID).rows)
    {
      auto id_field = row.fields.at(0);
      if (checkID(id_field))
      {
        json j_icon;
        j_icon["iconID"] = row.fields.at(1).int_val;
        j_icon["iconState"] = row.fields.at(2).int_val;
        j_object["icons"] += j_icon;
      }
    }

    int fold_a = objID / 256;
    int fold_b = fold_a / 256;

    std::string elem_objects = path_objects + "/" +
      std::to_string(fold_b) + "/" +
      std::to_string(fold_a) + "/" +
      std::to_string(objID);


    std::ofstream object_file = make_json_file(elem_objects);
    try
    {
      object_file << std::setw(2) << j_object << std::endl;
    }
    catch (nlohmann::detail::type_error err)
    {
      // TODO: Investigate why some strings are invalid UTF-8
      std::cerr << "Error '" << err.what() << " while processing PK " << objID << std::endl;
    }
    object_file.close();

    ++it;
  }

  json j_objects_type_index;
  std::string path_objects_by_type = path_objects + "/groupBy/type";
  std::string index_objects_by_type = path_objects_by_type + "/index";

  for (json::iterator it = j_objects_by_type.begin(); it != j_objects_by_type.end(); ++it)
  {
    j_objects_type_index["types"] += it.key();
    std::string elem_object_type = path_objects_by_type + "/" + it.key();
    std::ofstream type_file = make_json_file(elem_object_type);
    type_file << std::setw(2) << it.value() << std::endl;
    type_file.close();
  }

  std::ofstream type_index_file = make_json_file(index_objects_by_type);
  type_index_file << std::setw(2) << j_objects_type_index << std::endl;
  type_index_file.close();
}

int fdb_read(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: fdb read <file>" << std::endl;
        return 1;
    }

    assembly::database::schema schema;
    assembly::database::io::read_from_file(argv[1], schema);

    std::string path_tables = "tables";
    std::string path_zones = "zones";
    std::string path_behaviors = "behaviors";
    std::string path_objects = "objects";

    store_zone_tables(schema, path_tables, path_zones);

    store_single_table(schema, path_tables, "AccessoryDefaultLoc");
    store_single_table(schema, path_tables, "BrickColors");
    store_single_table(schema, path_tables, "EventGating");
    store_single_table(schema, path_tables, "FeatureGating");
    store_single_table(schema, path_tables, "Factions");
    store_single_table(schema, path_tables, "Release_Version");
    store_single_table(schema, path_tables, "SubscriptionPricing");
    store_single_table(schema, path_tables, "BrickIDTable");

    store_behavior_tables(schema, path_behaviors);
    store_unpaged_table(schema, path_tables, "SkillBehavior");

    // Components
    store_unpaged_table(schema, path_tables, "PackageComponent");
    store_unpaged_table(schema, path_tables, "PetComponent");
    store_unpaged_table(schema, path_tables, "RocketLaunchpadControlComponent");
    store_unpaged_table(schema, path_tables, "ProximityMonitorComponent");

    store_paged_table(schema, path_tables, "ScriptComponent");
    store_paged_table(schema, path_tables, "DestructibleComponent");
    store_paged_table(schema, path_tables, "VendorComponent");
    store_paged_table(schema, path_tables, "MinifigComponent");
    store_paged_table(schema, path_tables, "RebuildComponent");
    store_paged_table(schema, path_tables, "MovementAIComponent");
    store_paged_table(schema, path_tables, "BaseCombatAIComponent");
    store_paged_table(schema, path_tables, "ModuleComponent");
    store_paged_table(schema, path_tables, "CollectibleComponent");

    store_unpaged_table(schema, path_tables, "ActivityText");
    store_many_table(schema, path_tables, "ActivityRewards", "activity_rewards");
    store_many_table(schema, path_tables, "CurrencyTable", "currency_table");
    store_paged_table(schema, path_tables, "Activities");
    store_paged_table(schema, path_tables, "NpcIcons");

    // Missions
    store_missions_tables(schema);
    store_paged_table(schema, path_tables, "Missions");
    store_paged_table(schema, path_tables, "MissionEmail");
    store_paged_table(schema, path_tables, "MissionText");
    store_many_table(schema, path_tables, "MissionTasks", "tasks");

    // Minifig Decals
    store_paged_table(schema, path_tables, "MinifigDecals_Legs");
    store_paged_table(schema, path_tables, "MinifigDecals_Torsos");
    store_unpaged_table(schema, path_tables, "MinifigDecals_Eyebrows");
    store_unpaged_table(schema, path_tables, "MinifigDecals_Eyes");
    store_unpaged_table(schema, path_tables, "MinifigDecals_Mouths");

    store_many_table(schema, path_tables, "LootMatrix", "elements");
    store_many_table(schema, path_tables, "InventoryComponent", "items");
    store_many_table(schema, path_tables, "MissionNPCComponent", "missions");

    store_loot_tables(schema, path_tables);

    store_unpaged_table(schema, path_tables, "Icons");
    store_paged_table(schema, path_tables, "ItemComponent");
    store_paged_table(schema, path_tables, "PhysicsComponent");

    store_object_tables(schema, path_objects);

    store_paged_table(schema, path_tables, "RenderComponent");

    return 0;
}

int fdb_behaviors(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: fdb read <file>" << std::endl;
        return 1;
    }

    assembly::database::schema schema;
    assembly::database::io::read_from_file(argv[1], schema);

    const assembly::database::table names = schema.at("BehaviorTemplateName");
    const assembly::database::table templates = schema.at("BehaviorTemplate");
    const assembly::database::table parameters = schema.at("BehaviorParameter");

    json output;

    auto it = assembly::database::query::for_table(names);

    while (it)
    {
        const assembly::database::row& row = *it;
        int i = row.fields.at(0).int_val;

        output[std::to_string(i)]["name"] = row.fields.at(1).str_val;

        ++it;
    }

    it = assembly::database::query::for_table(parameters);

    while (it)
    {
        const assembly::database::row& row = *it;
        int bId = row.fields.at(0).int_val;

        int i = 0;
        for (const assembly::database::row& r : templates.at(bId).rows)
        {
            if (r.fields.at(0).int_val == bId)
            {
                i = r.fields.at(1).int_val;
                break;
            }
        }

        std::string key = row.fields.at(1).str_val;
        output[std::to_string(i)]["parameters"][key] = true;

        ++it;
    }

    std::cout << std::setw(2) << output << std::endl;

    return 0;
}

int fdb_convert(int argc, char** argv)
{
    if (argc <= 2)
    {
        std::cout << "Usage: fdb test <input> <output>" << std::endl;
        return 1;
    }

    Magick::Image img;
    img.read(argv[1]);
    img.write(argv[2]);

    return 0;
}

int fdb_all_tables(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: fdb test <database>" << std::endl;
        return 1;
    }

    std::string path = "docs/tables/all.rst";
    fs::ensure_dir_exists(path);
    std::ofstream ofile(path);

    ofile << "Table Overview" << std::endl;
    ofile << "==============" << std::endl;
    ofile << std::left << std::endl;

    assembly::database::schema fdb;
    if (assembly::database::io::read_from_file(argv[1], fdb) != 0) return 2;

    int colwidth = 50;
    int typewidth = 10;

    for (assembly::database::table& table : fdb.tables)
    {
        ofile << table.name << std::endl;
        ofile << std::string(table.name.size(), '-') << std::endl;
        ofile << std::endl;

        ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;
        ofile << std::setw(colwidth) << "Column" << "  " << std::setw(typewidth) << "Type" << std::endl;
        ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;

        for (assembly::database::column& column : table.columns)
        {
            ofile << std::setw(colwidth) << column.name << "  " << std::setw(typewidth) << types[(int) column.type] << std::endl;
        }

        ofile << std::string(colwidth, '=') << "  " << std::string(typewidth, '=') << std::endl;
        ofile << std::endl;

        ofile << table.slots.size() << " Slots" << std::endl;
        ofile << std::endl;
    }

    ofile.close();

}

const char* ctypes[] = {"void*", "int32_t", "err_t", "float", "std::string", "bool", "int64_t", "err2_t", "std::string" };

int fdb_header(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: fdb header <database>" << std::endl;
        return 1;
    }

    std::string path = "code/cdclient.hpp";
    std::string path2 = "code/cdclient.cpp";
    fs::ensure_dir_exists(path);
    fs::ensure_dir_exists(path2);
    std::ofstream ofile(path);
    std::ofstream ifile(path2);

    ofile << "#pragma once" << std::endl;
    ofile << std::left << std::endl;
    ofile << "#include <string>" << std::endl;
    ofile << "#include <iostream>" << std::endl;
    ofile << std::endl;
    ofile << "#include <assembly/database.hpp>" << std::endl;
    ofile << std::endl;

    ifile << "#include \"cdclient.hpp\"" << std::endl;
    ifile << std::endl;
    ofile << std::endl;

    assembly::database::schema fdb;
    if (assembly::database::io::read_from_file(argv[1], fdb) != 0) return 2;

    int typewidth = 15;

    for (assembly::database::table table: fdb.tables)
    {
        ofile << "// SlotCount: " << table.slots.size() << std::endl;
        ofile << "typedef struct" << std::endl;
        ofile << "{" << std::endl;

        ifile << "void readDB(" << table.name << "& entry, std::istream& file)" << std::endl;
        ifile << "{" << std::endl;

        for (assembly::database::column& column: table.columns)
        {
            ofile << "    " << std::setw(typewidth) << ctypes[(int) column.type] << " m_" << column.name << ";" << std::endl;
            ifile << "    readField(file, entry.m_" << column.name << ");" << std::endl;
        }

        ofile << "}" << std::endl;
        ofile << table.name << ";" << std::endl;
        ofile << std::endl;
        ofile << "void readDB(" << table.name << "& entry, std::istream& file);" << std::endl;
        ofile << std::endl;

        ifile << "}" << std::endl;
        ifile << std::endl;
    }

    ofile.close();
    ifile.close();
}

//int max(int a, int b)
//{
//    return (a < b) ? b : a;
//}
//
//void read_row(std::istream& file, std::ostream& ofile, int32_t row_data_addr, int* args, int* widths, int count)
//{
//    file.seekg(row_data_addr);
//
//    for (int k = 0; k < count; k++)
//    {
//        file.seekg(row_data_addr + 8 * args[k]);
//        int32_t data_type;
//        read(file, data_type);
//
//        int len = widths[k];
//
//        const char* before = (k > 0) ? ", " : "";
//        ofile << "\t" << ((k > 0) ? "  - " : "* - ");
//
//        switch (data_type)
//        {
//            case 1: // INT
//            case 5: // BOOL
//                int32_t int_val;
//                read(file, int_val);
//                ofile /*<< before << std::setw(len)*/ << int_val;
//                break;
//            case 3: // FLOAT
//                float float_val;
//                read(file, float_val);
//                ofile /*<< before << std::setw(len)*/ << float_val;
//                break;
//            case 4: // TEXT
//            case 8: // VARCHAR
//            {
//                int32_t string_addr;
//                read(file, string_addr);
//                std::string str = fdbReadString(file, string_addr);
//                trim(str);
//                //replace_all(str, "\"", "\\\"");
//                std::string str_val = str.empty() ? "" : "``" + str + "``";
//                ofile /*<< before /*<< std::setw(len)*/ << str_val;
//            }
//            break;
//            case 6: //BIGINT
//                int32_t int_addr;
//                read(file, int_addr);
//                file.seekg(int_addr);
//                int64_t bigint_val;
//                read(file, bigint_val);
//                ofile /*<< before /*<< std::setw(len)*/ << bigint_val;
//                break;
//            default:
//                int32_t val;
//                read(file, val);
//                ofile /*<< before /*<< std::setw(len)*/ << val;
//        }
//
//        ofile << std::endl;
//    }
//
//    //ofile << std::endl;
//}
//
//int read_row_infos(std::istream& file, std::ostream& ofile, int32_t row_info_addr, int* args, int* widths, int count)
//{
//    int32_t row_data_header_addr, column_count, row_data_addr;
//
//    while (row_info_addr != -1)
//    {
//        file.seekg(row_info_addr);
//
//        read(file, row_data_header_addr);
//        read(file, row_info_addr);
//
//        if (row_data_header_addr == -1) continue;
//
//        file.seekg(row_data_header_addr);
//        read(file, column_count);
//        read(file, row_data_addr);
//
//        if (row_data_addr == -1) continue;
//
//        /*std::cout << std::setw(6) << r << " ";*/
//
//        read_row(file, ofile, row_data_addr, args, widths, count);
//    }
//}
//
//int fdb_docs_table(int argc, char** argv)
//{
//    if (argc <= 3)
//    {
//        std::cout << "Usage: fdb docs-table <database> <table> <col_1> [<col_2> ... <col_n>]" << std::endl;
//        return 1;
//    }
//
//    FileDataBase fdb;
//    if (fdb.loadFromFile(argv[1]) != 0) return 2;
//
//    std::string table_name = argv[2];
//    fdb_table_t table = fdb.findTableByName(table_name);
//
//    if (table.name.empty()) return 5;
//
//    std::stringstream base_path("");
//    base_path << "docs/tables/" << table_name << ".rst";
//    fs::ensure_dir_exists(base_path.str());
//    std::ofstream ofile(base_path.str());
//    ofile << std::left;
//
//    ofile << table_name << std::endl;
//    ofile << std::string(table_name.size(), '=') << std::endl;
//    ofile << std::endl;
//
//    std::vector<std::string> columns;
//    for (int i = 3; i < argc; i++)
//    {
//        columns.push_back(argv[i]);
//    }
//
//    // std::stringstream underline("");
//    std::stringstream header("");
//    header /*<< "ID     "*/ << std::left;
//    /*underline << "====== ";*/
//
//    int i = 0;
//    int args[columns.size()];
//    int widths[columns.size()];
//    for (int j = 0; j < table.columns.size(); j++)
//    {
//        fdb_column_t& column = table.columns.at(j);
//        if (std::find(columns.begin(), columns.end(), column.name) != columns.end())
//        {
//            int len = max(lens[column.data_type], column.name.size());
//            header << ((i > 0) ? ", " : "") << column.name;
//            widths[i] = len;
//            args[i++] = j;
//        }
//    }
//
//    //ofile << underline.str() << std::endl;
//    ofile << ".. csv-table ::" << std::endl;
//    ofile << ":header: " << header.str() << std::endl;
//    ofile << std::endl;
//    //ofile << underline.str() << std::endl;
//
//    std::ifstream file(argv[1]);
//    if (!file.is_open()) return 4;
//
//    int cur = table.row_header_addr;
//    for (int r = 0; r < table.row_count; r++)
//    {
//        file.seekg(cur);
//        int32_t row_info_addr;
//
//        read(file, row_info_addr);
//        cur = file.tellg();
//
//        read_row_infos(file, ofile, row_info_addr, args, widths, i);
//    }
//
//    // ofile << underline.str() << std::endl;
//    ofile << std::endl;
//
//    file.close();
//    ofile.close();
//
//    return 0;
//}
//
//int fdb_docs_tables(int argc, char** argv)
//{
//    if (argc <= 3)
//    {
//        std::cout << "Usage: fdb docs-tables <database> <table> <col_1> [<col_2> ... <col_n>]" << std::endl;
//        return 1;
//    }
//
//    std::string arg1(argv[1]);
//    bool subheader = false;
//    if (arg1 == "--subheader" || arg1 == "-s")
//    {
//        subheader = true;
//    }
//
//    FileDataBase fdb;
//    if (fdb.loadFromFile(argv[1]) != 0) return 2;
//
//    std::string table_name = argv[2];
//    fdb_table_t table = fdb.findTableByName(table_name);
//
//    if (table.name.empty()) return 5;
//
//    std::stringstream base_path("");
//    base_path << "docs/tables/" << table_name << ".rst";
//    fs::ensure_dir_exists(base_path.str());
//    std::ofstream index_file(base_path.str());
//
//    std::cout << base_path.str() << std::endl;
//    index_file << table_name << std::endl;
//    index_file << std::string(table_name.size(), '=') << std::endl;
//    index_file << std::endl;
//    index_file << "Rows:" << table.row_count << std::endl << std::endl;
//    index_file << std::endl;
//    index_file << ".. toctree::" << std::endl;
//    index_file << "\t:maxdepth: 1" << std::endl;
//    index_file << "\t:caption: Contents:" << std::endl;
//    index_file << std::endl;
//
//    std::vector<std::string> columns;
//    for (int i = 3; i < argc; i++)
//    {
//        columns.push_back(argv[i]);
//    }
//
//    //std::stringstream underline("");
//    std::stringstream header("");
//    header /*<< "ID     "*/ << std::left;
//    /*underline << "====== ";*/
//
//    int i = 0;
//    int args[columns.size()];
//    int widths[columns.size()];
//    for (int j = 0; j < table.columns.size(); j++)
//    {
//        fdb_column_t& column = table.columns.at(j);
//        if (std::find(columns.begin(), columns.end(), column.name) != columns.end())
//        {
//            int len = max(lens[column.data_type], column.name.size());
//            header << "\t" << ((i > 0) ? "  - " : "* - ") << column.name << std::endl;
//            // underline << ((i > 0) ? "  " : "") << std::string(len, '=');
//            widths[i] = len;
//            args[i++] = j;
//        }
//    }
//
//    std::ofstream ofile;
//    int fileid = -1;
//
//    std::ifstream file(argv[1]);
//    if (!file.is_open()) return 4;
//
//    int cur = table.row_header_addr;
//    for (int r = 0; r < table.row_count; r++)
//    {
//        file.seekg(cur);
//        int32_t row_info_addr, row_data_header_addr, column_count, row_data_addr;
//
//        read(file, row_info_addr);
//        cur = file.tellg();
//
//        bool started = (row_info_addr != -1);
//        if (started)
//        {
//            int entries_per_page = 500;
//
//            int newfid = r / entries_per_page;
//            bool newfile = (newfid != fileid);
//            if (newfile)
//            {
//                if (ofile.is_open()) ofile.close();
//
//                fileid = newfid;
//                std::stringstream path("");
//                path << "docs/tables/" << table.name << "/" << fileid << ".rst";
//                std::string path_str = path.str();
//                fs::ensure_dir_exists(path_str);
//                std::cout << path_str << std::endl;
//                ofile.open(path_str);
//                if (!ofile.is_open()) return 7;
//
//                index_file << "\t" << table.name << "/" << fileid << std::endl;
//
//                std::stringstream title("");
//                title << (fileid * entries_per_page) << " to " << ((fileid + 1) * entries_per_page - 1);
//                std::string title_str = title.str();
//                ofile << std::left;
//                ofile << title_str << std::endl;
//                ofile << std::string(title_str.size(), '=') << std::endl;
//                ofile << std::endl;
//            }
//
//            if (subheader)
//            {
//                ofile << table.name << " #" << r << std::endl;
//                ofile << std::string(table.name.size() + log10(r) + 3, '-') << std::endl;
//                ofile << std::endl;
//            }
//
//            if (subheader || newfile)
//            {
//                ofile << ".. list-table ::" << std::endl;
//                ofile << "\t:widths: auto" << std::endl;
//                ofile << "\t:header-rows: 1" << std::endl;
//                ofile << std::endl;
//                ofile << header.str();
//            }
//
//            read_row_infos(file, ofile, row_info_addr, args, widths, i);
//
//            if (subheader) ofile << std::endl;
//        }
//    }
//
//    if (ofile.is_open()) ofile.close();
//
//    index_file << std::endl;
//    index_file.close();
//    return 0;
//}
//
