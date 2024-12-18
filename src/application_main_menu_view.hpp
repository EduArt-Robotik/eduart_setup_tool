/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "application_view.hpp"

#include <cstddef>
#include <memory>
#include <string>

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
  bool processInput(const ncinput& input) override;
  const std::size_t selectedItem() const {
    return static_cast<std::size_t>(_selected_item);
  }

private:
  ncselector* _selector = nullptr;
  ncplane* _selector_plane = nullptr;
  int _selected_item = -1;
};

} // end namespace setup tool
} // end namespace eduart
