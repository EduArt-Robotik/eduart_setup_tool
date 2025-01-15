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

  // Platform
  struct Platform {
    std::string name; // platform name
    std::string path; // path to docker folder
  };
  std::vector<Platform> platform;
};

struct EduArtSoftwareService {

};

} // end namespace setup tool
} // end namespace eduart


namespace std {

inline std::ostream& operator<<(std::ostream& os, const eduart::setup_tool::EduArtSoftware& software)
{
  os << "{name: " << software.name << ", ";
  os << "version: [";

  for (const auto& version : software.version) {
    os << version.major << '.' << version.minor << '.' << version.patch;
    if (version.appendix.empty() == false) os << '-' << version.appendix;
    os << ", ";
  }

  os << "], url: " << software.url << ", branch: " << software.branch << "}";

  return os;
}

} // end namespace std