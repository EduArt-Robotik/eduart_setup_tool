#include "application_main_menu.hpp"
#include "application_main_menu_view.hpp"
#include "application_state.hpp"

#include <notcurses/notcurses.h>

#include <memory>
#include <iostream>
#include <thread>

namespace eduart {
namespace setup_tool {

using namespace std::chrono_literals;

ApplicationMainMenu::ApplicationMainMenu(std::shared_ptr<ncpp::NotCurses>& not_curses)
  : ApplicationSateWithView<ApplicationMainMenuView>(std::make_unique<ApplicationMainMenuView>(not_curses), not_curses)
{

}

std::shared_ptr<ApplicationSate> ApplicationMainMenu::process()
{
  // Rendering View
  view().show();
  
  // Processing Input
  auto input = getInput();

  while (input != nullptr && input->id != 'q') {
    input = getInput();
    view().processInput(*input);
  }

  const auto tmp = view().selectedItem();
  std::cout << "selected item: " << tmp << std::endl;
    std::this_thread::sleep_for(10s);

  return nullptr;
}

} // end namespace setup tool
} // end namespace eduart
