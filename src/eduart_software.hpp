/*
 * Copyright EduArt Robotik GmbH 2025
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include <string>
#include <ostream>
#include <vector>

namespace eduart {
namespace setup_tool {

struct EduArtSoftware {
  std::string name;

  // Platform
  struct Platform {
    std::string name; // platform name
    std::string path; // path to docker folder
    std::string systemd_file;
    std::string docker_compose_file;
  };
  std::vector<Platform> platform;
};

struct EduArtSoftwarePackage {
  std::string name;
  std::string url;
  std::string branch;

  // Version
  struct Version {
    unsigned int major;
    unsigned int minor;
    unsigned int patch;
    std::string appendix;
  };
  std::vector<Version> version;

  // Software
  std::vector<EduArtSoftware> software;
};

} // end namespace setup tool
} // end namespace eduart


namespace std {

inline std::ostream& operator<<(std::ostream& os, const eduart::setup_tool::EduArtSoftware::Platform& platform)
{
  os << "{name: " << platform.name << ", path: " << platform.path << ", systemd_file: " << platform.systemd_file;
  os << ", docker_compose_file: " << platform.docker_compose_file << "}";
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const eduart::setup_tool::EduArtSoftware& software)
{
  os << "{name: " << software.name << ", ";
  os << "platform: [";

  for (const auto& platform : software.platform) {
    os << platform << ", ";
  }

  os << "]";

  return os;
}

inline std::ostream& operator<<(std::ostream& os, const eduart::setup_tool::EduArtSoftwarePackage& package)
{
  os << "{name: " << package.name;
  os << ", url: " << package.url;
  os << ", branch: "  << package.branch;
  os << ", version: [";
  for (const auto& version : package.version) {
    os << version.major << '.' << version.minor << '.' << version.patch;
    if (version.appendix.empty() == false) os << '-' << version.appendix;
    os << ", ";
  }

  return os;
}

} // end namespace std