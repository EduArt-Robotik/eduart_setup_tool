#include "eduart_software_querier.hpp"

#include "eduart_software.hpp"
#include "shell_executer.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>

namespace eduart {
namespace setup_tool {

using json = nlohmann::json;

static void from_json(const json& j, EduArtSoftware& software)
{
  j.at("name").get_to(software.name);
  j.at("url").get_to(software.url);
}

static std::vector<EduArtSoftware> get_software_from_file(const std::string& software_catalog_file)
{
  std::vector<EduArtSoftware> software;
  std::ifstream file(software_catalog_file);

  if (file.is_open() == false) {
    throw std::runtime_error("EduArtSoftwareQuerier: can't open software catalog file.");
  }

  const auto parsed_json = json::parse(file);
  
  std::cout << parsed_json["software"][0].template get<EduArtSoftware>() << std::endl;

  for (const auto& [key, value] : parsed_json.items()) {
    std::cout << "key: " << key << ", value: " << value << std::endl;
    std::cout << value.template get<EduArtSoftware>() << std::endl;
  }

  return software;
}

EduArtSoftwareQuerier::EduArtSoftwareQuerier(const std::string& software_catalog_file)
{
  get_software_from_file(software_catalog_file);
}

EduArtSoftwareQuerier::~EduArtSoftwareQuerier()
{

}

} // end namespace setup tool
} // end namespace eduart
