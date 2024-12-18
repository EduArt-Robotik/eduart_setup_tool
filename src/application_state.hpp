/*
 * Copyright EduArt Robotik GmbH 2024
 *
 * Author: Christian Wendt (christian.wendt@eduart-robotik.com)
 */
#pragma once

#include "application_view.hpp"

#include <memory>

namespace eduart {
namespace setup_tool {

class ApplicationSate
{
public:
  virtual ~ApplicationSate() = default;

protected:
  ApplicationSate(std::shared_ptr<ncpp::NotCurses> not_curses)
    : _not_curses(not_curses)
  { }

public:
  /**
   * \brief Performs current state until it is finished. The next application state will be returned. If returned state is null it means there is no state after.
   */
  virtual std::shared_ptr<ApplicationSate> process() = 0;

  std::shared_ptr<ncinput> getInput();

protected:
  std::shared_ptr<ncpp::NotCurses> _not_curses;
};

template <class View>
class ApplicationSateWithView : public ApplicationSate
{
public:
  ~ApplicationSateWithView() override = default;

protected:
  ApplicationSateWithView(std::unique_ptr<ApplicationView> view, std::shared_ptr<ncpp::NotCurses> not_curses)
    : ApplicationSate(not_curses)
    , _view(std::move(view))
  { }

  inline View& view() { return static_cast<View&>(*_view); }

private:
  std::unique_ptr<ApplicationView> _view;
};

} // end namespace setup tool
} // end namespace eduart
