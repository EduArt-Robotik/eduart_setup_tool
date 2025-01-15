#include "eduart_software_querier.hpp"

#include "eduart_software.hpp"
#include "shell_executer.hpp"

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <regex>

namespace eduart {
namespace setup_tool {

using json = nlohmann::json;
using nlohmann::json;

static void from_json(const json& j, EduArtSoftware& software)
{
  j.at("name").get_to(software.name);
  j.at("url").get_to(software.url);
  j.at("branch").get_to(software.branch);
}

static void from_json(const json& j, std::vector<EduArtSoftware::Version>& version)
{
  std::regex pattern("^([0-9]*).([0-9]*).([0-9]*)-?([a-z]*)$");
  std::smatch match;

  for (const auto& entry : j) {
    const std::string entry_string = entry.get<std::string>();
    
    if (std::regex_search(entry_string, match, pattern) == false) {
      throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
    }
    if (match.size() != 5) {
      throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
    }

    version.push_back(EduArtSoftware::Version{
      static_cast<unsigned int>(std::stoi(match[1])),
      static_cast<unsigned int>(std::stoi(match[2])),
      static_cast<unsigned int>(std::stoi(match[3])),
      match[4]
    });
  }
}

static void from_json(const json& j, std::vector<EduArtSoftware::Platform>& platform)
{

}

static std::vector<EduArtSoftware> get_software_from_file(const std::string& software_catalog_file)
{
  std::vector<EduArtSoftware> software;
  std::ifstream file(software_catalog_file);

  if (file.is_open() == false) {
    throw std::runtime_error("EduArtSoftwareQuerier: can't open software catalog file.");
  }

  const auto parsed_json = json::parse(file);

  for (const auto& entry : parsed_json["software"]) {
    std::cout << entry.get<EduArtSoftware>() << std::endl;
    software.push_back(entry.get<EduArtSoftware>());
  }

  return software;
}

static void determine_software_details(std::vector<EduArtSoftware>& software)
{
  for (auto& entry : software) {
    const std::string command =
      "curl https://raw.githubusercontent.com/EduArt-Robotik/" + entry.name + "/" + entry.branch + "/eduart.service.json";
    ShellExecuter executer(command);

    if (executer.returnCode() != 0 || executer.stdOut().find("404: Not Found") != std::string::npos) {
      // error ocurred during command executing
      continue;
    }

    const auto parsed_json = json::parse(executer.stdOut());
    entry.version  = std::move(parsed_json["version"].get<std::vector<EduArtSoftware::Version>>());
    entry.platform = std::move(parsed_json["platform"].get<std::vector<EduArtSoftware::Platform>>());
  }
}


EduArtSoftwareQuerier::EduArtSoftwareQuerier(const std::string& software_catalog_file)
{
  auto sofware = get_software_from_file(software_catalog_file);
  determine_software_details(sofware);

  for (const auto& entry : sofware) {
    std::cout << entry << std::endl;
  }
}

EduArtSoftwareQuerier::~EduArtSoftwareQuerier()
{

}

} // end namespace setup tool
} // end namespace eduart
