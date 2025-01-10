/*
 * Copyright EduArt Robotik GmbH 2025
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include <string>
#include <vector>

#include "eduart_software.hpp"

namespace eduart {
namespace setup_tool {

class EduArtSoftwareQuerier
{
public:
  EduArtSoftwareQuerier(const std::string& software_catalog_file);
  virtual ~EduArtSoftwareQuerier();

  inline const std::vector<EduArtSoftware>& software() const { return _software; }

private:
  std::vector<EduArtSoftware> _software;
};

} // end namespace setup tool
} // end namespace eduart
