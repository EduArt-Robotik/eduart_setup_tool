/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "application_state.hpp"

#include <memory>

namespace eduart {
namespace setup_tool {

class ApplicationMainMenu : public ApplicationSate
{
public:
  ApplicationMainMenu(std::shared_ptr<ncpp::NotCurses>& not_curses);
  ~ApplicationMainMenu() override = default;

  std::shared_ptr<ApplicationSate> perform() override;

private:

};

} // end namespace setup tool
} // end namespace eduart
