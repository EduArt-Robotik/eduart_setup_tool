/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include <string>

namespace eduart {
namespace setup_tool {

class ShellExecuter
{
public:
  ShellExecuter(const std::string& command);

  inline const std::string& stdOut() const { return _stdout; }
  inline int returnCode() const { return _return_code; }

private:
  std::string _stdout;
  int _return_code = 0;
};

} // end namespace setup tool
} // end namespace eduart
