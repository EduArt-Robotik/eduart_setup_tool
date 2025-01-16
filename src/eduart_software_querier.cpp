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

static void from_json(const json& j, EduArtSoftwarePackage& package)
{
  j.at("name").get_to(package.name);
  j.at("url").get_to(package.url);
  j.at("branch").get_to(package.branch);
}

static void from_json(const json& j, EduArtSoftware::Platform& platform)
{
  j.at("name").get_to(platform.name);
  j.at("path").get_to(platform.path);
  j.at("serviced_file").get_to(platform.systemd_file);
  j.at("docker_compose_file").get_to(platform.docker_compose_file);
}

static void from_json(const json& j, EduArtSoftware& software)
{
  j.at("name").get_to(software.name);

  for (const auto& entry : j["platform"]) {
    software.platform.emplace_back(entry.get<EduArtSoftware::Platform>());
  }
}

// static void from_json(const json& j, std::vector<EduArtSoftware::Version>& version)
// {
//   std::regex pattern("^([0-9]*).([0-9]*).([0-9]*)-?([a-z]*)$");
//   std::smatch match;

//   for (const auto& entry : j) {
//     const std::string entry_string = entry.get<std::string>();
    
//     if (std::regex_search(entry_string, match, pattern) == false) {
//       throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
//     }
//     if (match.size() != 5) {
//       throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
//     }

//     version.push_back(EduArtSoftware::Version{
//       static_cast<unsigned int>(std::stoi(match[1])),
//       static_cast<unsigned int>(std::stoi(match[2])),
//       static_cast<unsigned int>(std::stoi(match[3])),
//       match[4]
//     });
//   }
// }

static std::vector<EduArtSoftwarePackage> get_software_packages_from_catalog(const std::string& software_catalog_file)
{
  std::vector<EduArtSoftwarePackage> software;
  std::ifstream file(software_catalog_file);

  if (file.is_open() == false) {
    throw std::runtime_error("EduArtSoftwareQuerier: can't open software catalog file.");
  }

  const auto parsed_json = json::parse(file);

  for (const auto& entry : parsed_json["package"]) {
    software.push_back(entry.get<EduArtSoftwarePackage>());
  }

  return software;
}

static void determine_software_package_versions(EduArtSoftwarePackage& package)
{
  std::cout << "using command: " << "git ls-remote --tags " << package.url << std::endl;
  ShellExecuter executer("git ls-remote --tags " + package.url);

  if (executer.returnCode() != 0) {
    throw std::runtime_error("EduArtSoftwareQuerier: can't query tags from github.");
  }

  std::istringstream result(executer.stdOut());
  std::regex pattern("[a-f|0-9]*refs/tags/([0-9]*).([0-9]*).([0-9]*)-?([a-z]*)$");
  std::string line;

  while (std::getline(result, line)) {
    std::cout << "processing line: " << line << std::endl;
    std::smatch match;

    if (std::regex_search(line, match, pattern) == false) {
      throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
    }
    if (match.size() != 5) {
      throw std::runtime_error("EduArtSoftwareQuerier: version string is invalid.");
    }

    package.version.push_back(EduArtSoftwarePackage::Version{
      static_cast<unsigned int>(std::stoi(match[1])),
      static_cast<unsigned int>(std::stoi(match[2])),
      static_cast<unsigned int>(std::stoi(match[3])),
      match[4]
    });
  }  
}

static std::vector<EduArtSoftware> get_software_from_github(const EduArtSoftwarePackage& package)
{
  // requesting eduart service config from github
  const std::string command =
    "curl https://raw.githubusercontent.com/EduArt-Robotik/" + package.name + "/" + package.branch + "/eduart.service.json";
  ShellExecuter executer(command);

  if (executer.returnCode() != 0 || executer.stdOut().find("404: Not Found") != std::string::npos) {
    // error ocurred during command executing or file was not found
    return { };
  }
  //else: got service config

  // parsing 
  const auto parsed_json = json::parse(executer.stdOut());
  std::vector<EduArtSoftware> software;

  for (const auto& entry : parsed_json["software"]) {
    software.emplace_back(entry.get<EduArtSoftware>());
  }

  return software;
}


EduArtSoftwareQuerier::EduArtSoftwareQuerier(const std::string& software_catalog_file)
{
  auto packages = get_software_packages_from_catalog(software_catalog_file);

  for (auto& package : packages) {
    determine_software_package_versions(package);
    package.software = get_software_from_github(package);
  }

  for (const auto& entry : packages) {
    std::cout << entry << std::endl;
  }
}

EduArtSoftwareQuerier::~EduArtSoftwareQuerier()
{

}

} // end namespace setup tool
} // end namespace eduart
