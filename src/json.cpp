#include "json.hpp"
#include <assembly/utf.hpp>

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
