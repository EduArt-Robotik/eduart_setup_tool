/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "application_view.hpp"

#include <memory>

struct ncselector;
struct ncplane;

namespace eduart {
namespace setup_tool {

class ApplicationMainMenuView : public ApplicationView
{
public:
  ApplicationMainMenuView(std::shared_ptr<ncpp::NotCurses>& not_curses);
  ~ApplicationMainMenuView() override;

  void show() override;
  void selectNextItem();
  void selectPreviousItem();

private:
  ncselector* _selector = nullptr;
  ncplane* _selector_plane = nullptr;
};

} // end namespace setup tool
} // end namespace eduart
