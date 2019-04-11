#include "json.hpp"

#include <assembly/utf.hpp>
#include <limits>

using namespace nlohmann;


namespace std
{
    void to_json(nlohmann::json& j, const u16string& str)
    {
        j = utf::to_utf8(str);
    }

    void from_json(const nlohmann::json& j, u16string& str)
    {
        str = utf::from_utf8(j.get<string>());
    }
}

namespace assembly::common
{
    void to_json(json& j, const vector3f& v)
    {
        j = json{{"x", v.x}, {"y", v.y}, {"z", v.z}};
    }

    void from_json(const json& j, vector3f& v)
    {
        v.x = j.at("x").get<float>();
        v.y = j.at("y").get<float>();
        v.z = j.at("z").get<float>();
    }

    void to_json(json& j, const quaternion& q)
    {
        j = json{{"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w}};
    }

    void from_json(const json& j, quaternion& q)
    {
        q.x = j.at("x").get<float>();
        q.y = j.at("y").get<float>();
        q.z = j.at("z").get<float>();
        q.w = j.at("w").get<float>();
    }

    void to_json(json& j, const position& p)
    {
        j = json{{"pos", p.pos}, {"rot", p.rot}};
    }

    void from_json(const json& j, position& v)
    {
        v.pos = j.at("pos").get<vector3f>();
        v.rot = j.at("rot").get<quaternion>();
    }
}

namespace assembly::database
{
  void to_json(nlohmann::json& j, const field& f)
  {
    switch(f.type)
    {
        case assembly::database::value_type::NOTHING:
          j = json();
          break;
        case assembly::database::value_type::BOOLEAN:
          j = (f.int_val != 0);
          break;
        case assembly::database::value_type::INTEGER:
          j = f.int_val;
          break;
        case assembly::database::value_type::FLOAT:
          j = f.flt_val;
          break;
        case assembly::database::value_type::BIGINT:
          j = f.i64_val;
          break;
        case assembly::database::value_type::VARCHAR:
        case assembly::database::value_type::TEXT:
          j = utf::from_latin_1(f.str_val);
          break;
    }
  }

  void from_json(const nlohmann::json& j, field& f)
  {
    int64_t val;

    switch(j.type()) {
      case nlohmann::json::value_t::null:
        f.int_val = 0;
        f.type = assembly::database::value_type::NOTHING;
        break;
      case nlohmann::json::value_t::boolean:
        f.int_val = j ? 1 : 0;
        f.type = assembly::database::value_type::BOOLEAN;
        break;
      case nlohmann::json::value_t::string:
        f.str_val = utf::to_latin_1(j);
        f.type = assembly::database::value_type::VARCHAR;
        break;
      case nlohmann::json::value_t::number_integer:
      case nlohmann::json::value_t::number_unsigned:
        val = j;
        if (val > std::numeric_limits<int32_t>::max() || val < std::numeric_limits<int32_t>::min()) {
          f.i64_val = j;
          f.type = assembly::database::value_type::BIGINT;
        } else {
          f.int_val = j;
          f.type = assembly::database::value_type::INTEGER;
        }
        break;
      case nlohmann::json::value_t::number_float:
        f.flt_val = j;
        f.type = assembly::database::value_type::FLOAT;
      default:
        throw new std::runtime_error("Could not covert JSON to FDB Field");
    }
  }
}
