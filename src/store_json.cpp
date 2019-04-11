#include "store.hpp"
#include <assembly/filesystem.hpp>
#include <iomanip>

namespace paradox::data
{
  std::string store_json_t::to_path(const std::string& path) const
  {
      return "lu-json/" + path + ".json";
  }

  std::ofstream store_json_t::make_file(const std::string& path) const
  {
      std::string json_file = this->to_path(path);
      fs::ensure_dir_exists(json_file);
      return std::ofstream(json_file);
  }

  void store_json_t::save(const nlohmann::json& j, const std::string& path) const
  {
    std::ofstream of = this->make_file(path);
    of << std::setw(2) << j << std::endl;
    of.close();
  }
}
