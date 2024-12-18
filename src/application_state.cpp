#include "application_state.hpp"

#include <notcurses/notcurses.h>
#include <ncpp/NotCurses.hh>

namespace eduart {
namespace setup_tool {

std::shared_ptr<ncinput> ApplicationSate::getInput()
{
  std::shared_ptr<ncinput> input = std::make_shared<ncinput>();

  notcurses_get_blocking(_not_curses->get_notcurses(), input.get());

  return input;
}

} // end namespace setup tool
} // end namespace eduart
