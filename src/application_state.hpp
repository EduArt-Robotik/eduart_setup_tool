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
  virtual ~ApplicationSate();

protected:
  ApplicationSate(std::unique_ptr<ApplicationView> view) : _view(std::move(view)) { }

public:
  /**
   * \brief Performs current state until it is finished. The next application state will be returned. If returned state is null it means there is no state after.
   */
  virtual std::shared_ptr<ApplicationSate> perform() = 0;

  inline const ApplicationView& view() const { return *_view; }

protected:
  std::unique_ptr<ApplicationView> _view;
};

template <class View>
class ApplicationSateViewCaster : public ApplicationSate
{
protected:
  inline View& cast() { return static_cast<View&>(*_view); }
};

} // end namespace setup tool
} // end namespace eduart
