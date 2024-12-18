/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "application_main_menu_view.hpp"
#include "application_state.hpp"

#include <memory>

namespace eduart {
namespace setup_tool {

class ApplicationMainMenu : public ApplicationSateWithView<ApplicationMainMenuView>
{
public:
  ApplicationMainMenu(std::shared_ptr<ncpp::NotCurses>& not_curses);
  ~ApplicationMainMenu() override = default;

  std::shared_ptr<ApplicationSate> process() override;

private:

};

} // end namespace setup tool
} // end namespace eduart
