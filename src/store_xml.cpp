#include "store.hpp"
#include <assembly/filesystem.hpp>

namespace paradox::data
{
  std::string store_xml_t::to_path(const std::string& path) const
  {
      return "lu-xml/" + path + ".xml";
  }

  std::ofstream store_xml_t::make_file(const std::string& path) const
  {
      std::string xml_file = this->to_path(path);
      fs::ensure_dir_exists(xml_file);
      return std::ofstream(xml_file);
  }
}
