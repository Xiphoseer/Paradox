#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace paradox::data
{
  class store_t
  {
  public:
    virtual std::string to_path(const std::string& str) const = 0;
    virtual std::ofstream make_file(const std::string& path) const = 0;
    virtual ~store_t() = default;
  };

  typedef std::unique_ptr<store_t> store;

  class store_xml_t : public store_t
  {
  public:
    std::string to_path(const std::string& str) const override;
    std::ofstream make_file(const std::string& path) const override;
    ~store_xml_t() = default;
  };

  class store_json_t : public store_t
  {
  public:
    std::string to_path(const std::string& str) const override;
    std::ofstream make_file(const std::string& path) const override;
    void save(const nlohmann::json& j, const std::string& path) const;
    ~store_json_t() = default;
  };
}
