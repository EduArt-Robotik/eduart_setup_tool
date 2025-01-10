/*
 * Copyright EduArt Robotik GmbH 2025
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include <string>
#include <ostream>

namespace eduart {
namespace setup_tool {

struct EduArtSoftware {
  std::string name;
  std::string url;
  struct {
    unsigned int major;
    unsigned int minor;
    unsigned int patch;
  } version;
};

} // end namespace setup tool
} // end namespace eduart


namespace std {

inline std::ostream& operator<<(std::ostream& os, const eduart::setup_tool::EduArtSoftware& software)
{
  os << "{name: " << software.name << ", version: ";
  os << software.version.major << '.' << software.version.minor << '.' << software.version.patch;
  os << ", url: " << software.url << "}";

  return os;
}

} // end namespace std