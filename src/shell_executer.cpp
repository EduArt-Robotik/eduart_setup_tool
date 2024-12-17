#include "shell_executer.hpp"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <stdexcept>

namespace eduart {
namespace setup_tool {

ShellExecuter::ShellExecuter(const std::string& command)
{
  // execute command and store output in file
  FILE* stdout = popen(command.c_str(), "r");

  if (stdout == nullptr) {
    // something went wrong --> collect error and throw it
    throw std::runtime_error(strerror(errno));
  }

  // store stdout in string
  constexpr std::size_t buffer_size = 1024;
  char c_string[buffer_size];

  while (fgets(c_string, sizeof(c_string), stdout) != nullptr) {
    _stdout += c_string;
  }

  // close stdout and get return code of executed command
  _return_code = pclose(stdout);

  if (_return_code < 0) {
    // something went wrong --> collect error and throw it
    throw std::runtime_error(strerror(errno));    
  }
}

} // end namespace setup tool
} // end namespace eduart
