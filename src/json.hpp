#pragma once
#include <assembly/types.hpp>
#include <nlohmann/json.hpp>


namespace std
{
    void to_json(nlohmann::json& j, const u16string& str);
    void from_json(const nlohmann::json& j, u16string& str);
}

namespace assembly::common
{
    void to_json(nlohmann::json& j, const vector3f& vec);
    void from_json(const nlohmann::json& j, vector3f& vec);

    void to_json(nlohmann::json& j, const quaternion& quat);
    void from_json(const nlohmann::json& j, quaternion& quat);

    void to_json(nlohmann::json& j, const position& pos);
    void from_json(const nlohmann::json& j, position& pos);
}
