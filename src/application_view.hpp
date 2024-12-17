/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include <memory>

namespace ncpp {
class NotCurses;
} // end namespace ncpp

namespace eduart {
namespace setup_tool {

class ApplicationView
{
protected:
  ApplicationView(std::shared_ptr<ncpp::NotCurses>& not_curses) : _not_curses(not_curses) { }

public:
  virtual ~ApplicationView() = default;

  /**
   * \brief Shows this application state on terminal.
   */
  virtual void show() = 0;

protected:
  const std::shared_ptr<ncpp::NotCurses> _not_curses;
};

} // end namespace setup tool
} // end namespace eduart
