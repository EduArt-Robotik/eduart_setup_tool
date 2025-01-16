/*
 * Copyright EduArt Robotik GmbH 2025
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "eduart_software.hpp"

namespace eduart {
namespace setup_tool {

class EduArtSoftwareService
{
public:
  EduArtSoftwareService(const EduArtSoftware& software);
  EduArtSoftwareService(const EduArtSoftwareService&) = delete;
  ~EduArtSoftwareService();

private:
  const EduArtSoftware _software;
  bool _is_installed = false;
  bool _is_running = false;
};

} // end namespace setup tool
} // end namespace eduart
