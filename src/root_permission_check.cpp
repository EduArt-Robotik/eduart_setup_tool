#include "root_permission_check.hpp"

#include "shell_executer.hpp"
#include <stdexcept>

namespace eduart {
namespace setup_tool {

const RootPermissionCheck& RootPermissionCheck::instance()
{
  static RootPermissionCheck checker;
  return checker;
}

RootPermissionCheck::RootPermissionCheck()
{
  ShellExecuter executer("whoami");

  if (executer.returnCode() != 0) {
    throw std::runtime_error("RootPermissionCheck: failed to execute check. Process returned with not equal 0");
  }
  _has_permission = executer.stdOut() == "root\n";
}

} // end namespace setup tool
} // end namespace eduart
