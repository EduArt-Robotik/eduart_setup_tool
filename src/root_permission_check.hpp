/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

namespace eduart {
namespace setup_tool {

class RootPermissionCheck
{
public:
  static const RootPermissionCheck& instance(); 

  bool hasPermission() const { return _has_permission; }

private:
  RootPermissionCheck();

  bool _has_permission = false;  
};

} // end namespace setup tool
} // end namespace eduart
