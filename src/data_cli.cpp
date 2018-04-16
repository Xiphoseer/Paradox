#include "data_cli.hpp"
#include "json.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>

#include <nlohmann/json.hpp>
#include <tinyxml2.h>

#include <assembly/cli.hpp>
#include <assembly/filesystem.hpp>
#include <assembly/zone_io.hpp>
#include <assembly/scene_io.hpp>
#include <assembly/utf.hpp>
#include <assembly/stringutil.hpp>
#include <assembly/namevalue.hpp>
#include <assembly/namevalue_io.hpp>
#include <assembly/zone_path_io.hpp>

using namespace nlohmann;

cli::opt_t data_options[] =
{
    { "zone",   &data_zone,   "Reads a zone file"   },
    { "level",  &data_level,  "Reads a level file"  },
    { "levels", &data_levels, "Reads level files"   },
    { "zones",  &data_zones,  "Reads zone files"    },
    { "test",   &data_test,   "Reads zone files"    },
    { "loc",    &data_loc,    "Process locale file" },
    { "help",   &help_data,   "Show this help"      },
    { 0, 0, 0 }
};

int main_data(int argc, char** argv)
{
	return cli::main("DataCLI", data_options, "data", argc, argv);
}

int help_data (int argc, char** argv)
{
	return cli::help("DataCLI", data_options, "Data manipulation tool");
}

namespace assembly::zone
{
    void to_json(json& j, const zone_file& zone)
    {
        j = {
            {"version", zone.version},
            {"revision", zone.revision},
            {"world_id", zone.world_id},
            {"spawnpoint", zone.spawnpoint},
            {"scenes", zone.scenes},
            {"something", zone.something},
            {"map_filename", zone.map_filename},
            {"map_name", zone.map_name},
            {"map_description", zone.map_description},
            {"transitions", zone.transitions}
        };
    }

    void to_json(json& j, const scene_ref& scene)
    {
        j = {
            {"filename", scene.filename},
            {"id", scene.id},
            {"is_audio", scene.is_audio},
            {"name", scene.name},
        };
    }

    void to_json(json& j, const scene_transition& trans)
    {
        j = {
            {"name", trans.name},
            {"points", trans.points}
        };
    }

    void to_json(json& j, const scene_transition_info& info)
    {
        j = {
            {"scene_id", info.scene_id},
            {"position", info.position}
        };
    }
}

namespace assembly::zone::path
{
    void to_json(json& j, const v3f_config& data)
    {
        j = {{"pos", data.pos}, {"config", data.config}};
    }

    void to_json(json& j, const path_data_movement& data)
    {
        j = {{"waypoints", data.waypoints}};
    }

    void to_json(json& j, const moving_platform_point& data)
    {
        j =
        {
            {"pos", data.pos},
            {"lock_player", data.lock_player},
            {"speed", data.speed},
            {"wait", data.wait},
            {"depart_sound", data.depart_sound},
            {"arrive_sound", data.arrive_sound}
        };
    }

    void to_json(json& j, const path_data_moving_platform& data)
    {
        j =
        {
            {"value_1", data.value_1},
            {"travel_sound", data.travel_sound},
            {"waypoints", data.waypoints}
        };
    }

    void to_json(json& j, const path_data_property& data)
    {
        j =
        {
            {"value_1", data.value_1},
            {"price", data.price},
            {"rental_time", data.rental_time},
            {"zone", data.zone},
            {"name", data.name},
            {"description", data.description},
            {"value_2", data.value_2},
            {"clone_limit", data.clone_limit},
            {"reputation_multiplier", data.reputation_multiplier},
            {"rental_time_unit", data.rental_time_unit},
            {"req_achievement", data.req_achievement},
            {"player_coord", data.player_coord},
            {"max_building_height", data.max_building_height},
            {"waypoints", data.waypoints}
        };
    }

    void to_json(json& j, const camera_path_entry& data)
    {
        j =
        {
            {"pos", data.pos},
            {"value_1", data.value_1},
            {"value_2", data.value_2},
            {"value_3", data.value_3},
            {"value_4", data.value_4},
            {"time", data.time},
            {"value_5", data.value_5},
            {"tension", data.tension},
            {"continuity", data.continuity},
            {"bias", data.bias}
        };
    }

    void to_json(json& j, const path_data_camera& data)
    {
        j =
        {
            {"value_1", data.value_1},
            {"next_path", data.next_path},
            {"waypoints", data.waypoints}
        };
    }

    void to_json(json& j, const spawner_path_entry& data)
    {
        j = {{"pos", data.pos}, {"config", data.config}};
    }

    void to_json(json& j, const path_data_spawner& data)
    {
        j =
        {
            {"spawned_lot", data.spawned_lot},
            {"respawn_time", data.respawn_time},
            {"max_to_spawn", data.max_to_spawn},
            {"number_to_maintain", data.number_to_maintain},
            {"object_id", data.object_id},
            {"activate_on_load", data.activate_on_load},
            {"waypoints", data.waypoints}
        };
    }

    void to_json(json& j, const path_data_showcase& data)
    {
        j = {{"waypoints", data.waypoints}};
    }

    void to_json(json& j, const race_path_entry& data)
    {
        j =
        {
            {"pos", data.pos},
            {"value_1", data.value_1},
            {"value_2", data.value_2},
            {"value_3", data.value_3},
            {"value_4", data.value_4},
            {"value_5", data.value_5}
        };
    }

    void to_json(json& j, const path_data_race& data)
    {
        j = {{"waypoints", data.waypoints}};
    }

    void to_json(json& j, const rail_path_entry& data)
    {
        j =
        {
            {"pos", data.pos},
            {"value_1", data.value_1},
            {"value_2", data.value_2},
            {"value_3", data.value_3},
            {"value_4", data.value_4},
            {"value_5", data.value_5},
            {"config", data.config}
        };
    }

    void to_json(json& j, const path_data_rail& data)
    {
        j = {{"waypoints", data.waypoints}};
    }

    void to_json(json& j, const path_data_entry& data)
    {
        j = json({});
        switch (data.type)
        {
            case path_type::movement:        j = data.d_movement;        break;
            case path_type::moving_platform: j = data.d_moving_platform; break;
            case path_type::property:        j = data.d_property;        break;
            case path_type::camera:          j = data.d_camera;          break;
            case path_type::spawner:         j = data.d_spawner;         break;
            case path_type::showcase:        j = data.d_showcase;        break;
            case path_type::race:            j = data.d_race;            break;
            case path_type::rail:            j = data.d_rail;            break;
        }
        j["path_version"] = data.path_version;
        j["behavior"] = data.behavior;
        j["name"] = utf::to_utf8(data.name);
        j["value_1"] = data.value_1;
        j["type"] = data.type;
    }

    void to_json(json& j, const zone_file_path_data& info)
    {
        j = {{"paths", info.paths}};
    }
}

json get_zone(std::string path)
{
    assembly::zone::zone_file zone;
    assembly::zone::io::read_from_file(path, zone);

    assembly::zone::path::zone_file_path_data path_data;
    assembly::zone::path::io::read_from_vector(zone.path_data, path_data);

    json j_zone(zone);
    j_zone["paths"] = json(path_data.paths);

    return j_zone;
}

json get_luz_files(std::string base, std::string path)
{
    json out;

    for (const std::string& file: fs::files_in_dir(base + path, "*.luz"))
    {
        out["."] += file;
        std::cout << path << file << std::endl;

        json j_zone = get_zone(base + path + file);
        std::string jpath = "lu-json/maps/" + path + file + ".json";

        std::cout << jpath << std::endl;

        fs::ensure_dir_exists(jpath);
        std::ofstream ofile(jpath);
        ofile << std::setw(2) << j_zone << std::endl;
        ofile.close();
    }

    for (const std::string& dir: fs::dirs_in_dir(base + path, "*"))
    {
        if (dir == "." || dir == "..") continue;
        out[dir] = get_luz_files(base, path + dir + "/");
    }
    return out;
}

int data_zones (int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: data zone <dir>" << std::endl;
        return 1;
    }

    //std::cout << std::setw(2) <<
       get_luz_files(argv[1], "")
    //   << std::endl
       ;

    return 0;
}

int data_zone (int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: data zone <file>" << std::endl;
        return 1;
    }


    json j_zone = get_zone(argv[1]);
    std::cout << std::setw(2) << j_zone << std::endl;

    return 0;
}

namespace assembly::namevalue
{
    void to_json(json& j, const any_value& val)
    {
        switch (val.type)
        {
            case value_type::string_v: j = val.v_string; break;
            case value_type::int32_v:  j = val.v_int32; break;
            case value_type::float_v:  j = val.v_float; break;
            case value_type::uint32_v: j = val.v_uint32; break;
            case value_type::bool_v:   j = val.v_bool; break;
            case value_type::int64_v:
            case value_type::id64_v:   j = val.v_int64; break;
            case value_type::binary_v: j = std::string(val.v_blob.begin(), val.v_blob.end()); break;
        }
    }
}

namespace assembly::scene
{
    void to_json(json& j, const chunk_1000& chnk)
    {
        j =
        {
            {"version", chnk.version},
            {"value_1", chnk.value_1},
            {"value_2", chnk.value_2},
            {"value_3", chnk.value_3},
            {"value_4", chnk.value_4}
        };
    }

    void to_json(json& j, const chunk_2000_id& id)
    {
        j =
        {
            {"id", id.id},
            {"value_1", id.value_1},
            {"value_2", id.value_2}
        };
    }

    void to_json(json& j, const chunk_2000& chnk)
    {
        j =
        {
            {"floats", chnk.floats},
            {"ids", chnk.ids},
            {"sky", {
                chnk.sky_file_1,
                chnk.sky_file_2,
                chnk.sky_file_3,
                chnk.sky_file_4,
                chnk.sky_file_5,
                chnk.sky_file_6,
            }}
        };
    }

    void to_json(json& j, const chunk_2001_object& obj)
    {
        assembly::namevalue::name_value_store config;
        try
        {
            assembly::namevalue::io::read_from_u16string(obj.settings, config, '\n');
        }
        catch (const std::exception& ex)
        {
            std::cerr << "An error occured: " << ex.what() << std::endl;
        }
        catch (const std::string& ex)
        {
            std::cerr << "An error occured: " << ex << std::endl;
        }
        catch ( ... )
        {
            std::cerr << "An error occured" << std::endl;
        }


        j =
        {
            {"id", obj.id},
            {"lot", obj.lot},
            {"value_1", obj.value_1},
            {"value_2", obj.value_2},
            {"pos", obj.pos},
            {"scale", obj.scale},
            {"settings", config},
            {"value_3", obj.value_3}
        };
    }

    void to_json(json& j, const chunk_2001& chnk)
    {
        j = {{"objects", chnk.objects}};
    }

    void to_json(json& j, const chunk_2002& chnk)
    {

    }

    void to_json(json& j, const chunk& chnk)
    {
        switch (chnk.type)
        {
            case chunk_type::chnk_1000: j = chnk.v1000; break;
            case chunk_type::chnk_2000: j = chnk.v2000; break;
            case chunk_type::chnk_2001: j = chnk.v2001; break;
            case chunk_type::chnk_2002: j = chnk.v2002; break;
        }
        j["_type"] = chnk.type;
    }

    void to_json(json& j, const scene_file& lvl)
    {
        j = {{"chunks", lvl.chunks}};
    }
}

int data_level (int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: data level <file>" << std::endl;
        return 1;
    }

    assembly::scene::scene_file lvl;
    assembly::scene::io::read_from_file(argv[1], lvl);

    json j_lvl = lvl;
    std::cout << std::setw(2) << j_lvl << std::endl;

    return 0;
}


json get_lvl_files(std::string base, std::string path)
{
    json out;

    for (const std::string& file: fs::files_in_dir(base + path, "*.lvl"))
    {
        out["."] += file;

        assembly::scene::scene_file lvl;
        assembly::scene::io::read_from_file(base + path + file, lvl);

        json j_lvl = lvl;
        std::string jpath = "lu-json/maps/" + path + file + ".json";

        fs::ensure_dir_exists(jpath);
        std::ofstream ofile(jpath);
        ofile << std::setw(2) << j_lvl << std::endl;
        ofile.close();
    }

    for (const std::string& dir: fs::dirs_in_dir(base + path, "*"))
    {
        if (dir == "." || dir == "..") continue;
        out[dir] = get_lvl_files(base, path + dir + "/");
    }
    return out;
}

int data_levels (int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: data levels <dir>" << std::endl;
        return 1;
    }

    //std::cout << std::setw(2) <<
       get_lvl_files(argv[1], "")
    //   << std::endl
    ;

    return 0;
}


struct D
{
    ~D(){ std::cout << "D DELETED" << std::endl; }
};

struct C
{
    ~C(){ std::cout << "C DELETED" << std::endl; }
};

struct A
{
    D a;
    D b;
};

struct B
{
    C a;
    C b;
};

struct X
{
    bool is_a;
    X (bool is_a) : is_a(is_a)
    {
        if (is_a) new (&a) A(); else new (&b) B();
    }

    union
    {
        A a;
        B b;
    };

    ~X()
    {
        if (is_a) a.~A(); else b.~B();
    }
};

int data_test (int argc, char** argv)
{
    X test(false);
    return 0;
}

using namespace tinyxml2;

int data_loc (int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Usage: data loc <file>" << std::endl;
        return 1;
    }

    std::cout << argv[1] << std::endl;

    XMLDocument doc;
    doc.LoadFile(argv[1]);

    XMLElement* root = doc.RootElement();
    std::cout << "Version: " << root->FloatAttribute("version", -1) << std::endl;

    XMLElement* phrases = root->FirstChildElement("phrases");
    std::cout << "Count:   " << phrases->IntAttribute("count") << std::endl;

    XMLElement* phrase = phrases->FirstChildElement();

    std::unordered_set<std::string> tables =
    {
        "Activities",
        "ActivityText",
        "Emotes",
        "ItemComponent",
        "ItemSets",
        "MissionEmail",
        "MissionTasks",
        "MissionText",
        "Missions",
        "Objects",
        "Preconditions",
        "PropertyTemplate",
        "RewardCodes",
        "SkillBehavior",
        "SpeedchatMenu",
        "UGBehaviorSounds",
        "WhatsCoolItemSpotlight",
        "WhatsCoolNewsAndTips",
        "ZoneLoadingTips",
        "ZoneTable",
        "brickAttributes"
    };

    json output;

    while (phrase != nullptr)
    {
        std::string id(phrase->Attribute("id"));

        std::size_t found = id.find("_");
        if (found != std::string::npos)
        {
            std::string table = id.substr(0, found);
            if (tables.find(table) != tables.end())
            {
                std::size_t f2 = id.find("_", found + 1);
                std::string pk = id.substr(found + 1, f2 - found - 1);
                std::string data = id.substr(f2 + 1);

                int i_pk = std::stoi(pk);
                std::string page = std::to_string(i_pk / 256);

                output[table][page][pk][data] = phrase->FirstChildElement()->GetText();
            }
        }

        phrase = phrase->NextSiblingElement();
    }

    fs::ensure_dir_exists("lu-json/locale/");
    for (const std::string& table : tables)
    {
        json index;
        fs::ensure_dir_exists("lu-json/locale/" + table + "/");

        for (json::iterator it = output[table].begin(); it != output[table].end(); ++it)
        {
            index["pages"] += std::stoi(it.key());
            std::ofstream out("lu-json/locale/" + table + "/" + it.key() + ".json");
            out << std::setw(2) << it.value() << std::endl;
            out.close();
        }

        std::ofstream out("lu-json/locale/" + table + "/index.json");
        out << std::setw(2) << index << std::endl;
        out.close();
    }

    return 0;
}
