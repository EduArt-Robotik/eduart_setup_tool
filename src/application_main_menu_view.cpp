#include "application_main_menu_view.hpp"
#include "application_view.hpp"

#include <ncpp/NotCurses.hh>
#include <notcurses/notcurses.h>

#include <stdexcept>
#include <cstring>

namespace eduart {
namespace setup_tool {

using namespace std::literals;

static ncselector_item menu_items[] = {
  { "Show Installed Software", "Checks which EduArt software is currently installed on the system."},
  { "Show Available Software", "Goes online and searches for EduArt software that could be installed."},
  { nullptr, nullptr }
};

static int get_item_index(const char* item)
{
  for (int i = 0; i < sizeof(menu_items) / sizeof(ncselector_item); ++i) {
    if (std::strcmp(menu_items[i].option, item) == 0) {
      return i;
    }
  }

  return -1;
}

ApplicationMainMenuView::ApplicationMainMenuView(std::shared_ptr<ncpp::NotCurses>& not_curses)
  : ApplicationView(not_curses)
{

}

ApplicationMainMenuView::~ApplicationMainMenuView()
{
  if (_selector != nullptr) {
    // frees also _selector_plane
    ncselector_destroy(_selector, nullptr);
  }
}

void ApplicationMainMenuView::show()
{
  auto plane = _not_curses->get_stdplane();

  // Background Image
  if (notcurses_canopen_images(_not_curses->get_notcurses())) {
    ncvisual* image = ncvisual_from_file("podium.png");
    ncvisual_options vopts = {
      .n = plane->to_ncplane(),
      .scaling = NCSCALE_STRETCH,
    };
  
    if(ncvisual_blit(_not_curses->get_notcurses(), image, &vopts) == NULL){
      throw std::runtime_error("ApplicationMainMenuView: can't draw image.");
    }
  
    ncvisual_destroy(image);
  }

  // Selector
  if (_selector_plane == nullptr) {
    ncplane_options nopts = {
      .y = 0,
      .x = 0,
      .rows = 1,
      .cols = 1,
      .userptr = NULL,
      .name = nullptr,
      .resizecb = NULL,
      .flags = 0,
    };
    nopts.x = plane->get_dim_x() / 2;
    nopts.y = plane->get_dim_y() / 2;

    ncselector_options sopts;
    memset(&sopts, 0, sizeof(sopts));
    sopts.maxdisplay = 10;
    sopts.items = menu_items;
    sopts.title = "EduArt Software Select";
    sopts.secondary = "pick one (you will die regardless)";
    sopts.footer = "press q to exit";
    sopts.defidx = 0;
    sopts.boxchannels   = NCCHANNELS_INITIALIZER(0x20, 0xe0, 0x40, 0x20, 0x20, 0x20);
    sopts.opchannels    = NCCHANNELS_INITIALIZER(0xe0, 0x80, 0x40, 0, 0, 0);
    sopts.descchannels  = NCCHANNELS_INITIALIZER(0x80, 0xe0, 0x40, 0, 0, 0);
    sopts.footchannels  = NCCHANNELS_INITIALIZER(0xe0, 0, 0x40, 0x20, 0, 0);
    sopts.titlechannels = NCCHANNELS_INITIALIZER(0xff, 0xff, 0x80, 0, 0, 0x20);
    uint64_t bgchannels = NCCHANNELS_INITIALIZER(0, 0x20, 0, 0, 0x20, 0);
    ncchannels_set_fg_alpha(&bgchannels, NCALPHA_BLEND);
    ncchannels_set_bg_alpha(&bgchannels, NCALPHA_BLEND);

    _selector_plane = ncplane_create(plane->to_ncplane(), &nopts);
    ncplane_set_base(_selector_plane, "", 0, bgchannels);
    _selector = ncselector_create(_selector_plane, &sopts);
  }

  _not_curses->render();
  _selected_item = get_item_index(ncselector_selected(_selector));

  if (_selected_item < 0) {
    throw std::runtime_error("ApplicationMainMenuView: something went wrong during selected item estimation. Item index not found.");
  }
}

bool ApplicationMainMenuView::processInput(const ncinput& input)
{
  if (ncselector_offer_input(_selector, &input)) {
    // was relevant
    _not_curses->render();
    _selected_item = get_item_index(ncselector_selected(_selector));
    return true;
  }

  return false;
}

} // end namespace setup tool
} // end namespace eduart
