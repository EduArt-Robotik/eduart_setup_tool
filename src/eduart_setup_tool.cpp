#include <memory>
#include <ncpp/CellStyle.hh>
#include <ncpp/NotCurses.hh>
#include <ncpp/Plane.hh>
#include <ncpp/Selector.hh>

#include <notcurses/notcurses.h>

#include <thread>
#include <unistd.h>
#include <vector>
#include <iostream>

#include "application_main_menu.hpp"
#include "shell_executer.hpp"
#include "root_permission_check.hpp"
#include "eduart_software_querier.hpp"

#include "application_main_menu_view.hpp"

using namespace std::chrono_literals;

int test_tui()
{
  notcurses_options options {
    NULL, NCLOGLEVEL_VERBOSE, 0, 0, 0, 0, 0
  };  
  ncpp::NotCurses not_curses;

  const ncpp::CellStyle style = not_curses.get_supported_styles();
  auto plane = not_curses.get_stdplane();

  // Image
  if (notcurses_canopen_images(not_curses.get_notcurses())) {
    ncvisual* image = ncvisual_from_file("podium.png");
    ncvisual_options vopts = {
      .n = plane->to_ncplane(),
      .scaling = NCSCALE_STRETCH,
    };
  
    if(ncvisual_blit(not_curses.get_notcurses(), image, &vopts) == NULL){
      return 1;
    }
  
    ncvisual_destroy(image);
  }

  // not_curses.render();
  // std::this_thread::sleep_for(2s);

  // Selector
  ncplane_set_fg_rgb(plane->to_ncplane(), 0x40f040);
  ncplane_putstr_aligned(plane->to_ncplane(), 0, NCALIGN_RIGHT, "selector widget demo");

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
  // ncpp::Plane sector_plane(plane, nopts);

  not_curses.render();
  std::this_thread::sleep_for(2s);

  std::vector<ncselector_item> items;
  items.push_back({"Item A", "Voll das gute Item!"});
  items.push_back({"Item B", "Voll das gute Item!"});
  // items.push_back({"Item C", "Voll das gute Item!"});
  // items.push_back({"Item D", "Voll das gute Item!"});
  // items.push_back({"Item E", "Voll das gute Item!"});
  // items.push_back({"Item F", "Voll das gute Item!"});
  // items.push_back({"Item G", "Voll das gute Item!"});
  // items.push_back({"Item H", "Voll das gute Item!"});
  // items.push_back({"Item I", "Voll das gute Item!"});
  // items.push_back({"Item J", "Voll das gute Item!"});
  // items.push_back({"Item K", "Voll das gute Item!"});
  // items.push_back({"Item Z", "Voll das gute Item!"});
  items.push_back({nullptr, nullptr}); // maybe it needs this line as termination
 
  ncselector_options sopts;
  memset(&sopts, 0, sizeof(sopts));
  sopts.maxdisplay = 10;
  sopts.items = items.data();
  sopts.title = "EduArt Software Select";
  sopts.secondary = "pick one (you will die regardless)";
  sopts.footer = "press q to exit (there is no exit)";
  sopts.defidx = 1;
  sopts.boxchannels = NCCHANNELS_INITIALIZER(0x20, 0xe0, 0x40, 0x20, 0x20, 0x20);
  sopts.opchannels = NCCHANNELS_INITIALIZER(0xe0, 0x80, 0x40, 0, 0, 0);
  sopts.descchannels = NCCHANNELS_INITIALIZER(0x80, 0xe0, 0x40, 0, 0, 0);
  sopts.footchannels = NCCHANNELS_INITIALIZER(0xe0, 0, 0x40, 0x20, 0, 0);
  sopts.titlechannels = NCCHANNELS_INITIALIZER(0xff, 0xff, 0x80, 0, 0, 0x20);
  uint64_t bgchannels = NCCHANNELS_INITIALIZER(0, 0x20, 0, 0, 0x20, 0);
  ncchannels_set_fg_alpha(&bgchannels, NCALPHA_BLEND);
  ncchannels_set_bg_alpha(&bgchannels, NCALPHA_BLEND);
  // ncpp::Selector selector(plane, &sopts);
 
  struct ncplane* seln;
  // seln = ncplane_create(plane->to_ncplane(), &nopts);
  // ncplane_set_base(seln, "", 0, bgchannels);
  // sopts.title = "short round title";
  seln = ncplane_create(plane->to_ncplane(), &nopts);
  ncplane_set_base(seln, "", 0, bgchannels);
  auto selector = ncselector_create(seln, &sopts);

  // selector.additem(items);

  not_curses.render();
  std::this_thread::sleep_for(10s);

  return 0;
}

void test_executer()
{
  eduart::setup_tool::ShellExecuter executer("test -f ls");

  std::cout << "stdout:\n" <<  executer.stdOut() << std::endl;
  std::cout << "return code = " << executer.returnCode() << std::endl;
}

void check_root_permission()
{
  std::cout << "has root permission = " << (eduart::setup_tool::RootPermissionCheck::instance().hasPermission() ? "yes" : "no") << std::endl;
}

void test_main_menu()
{
  notcurses_options options {
    NULL, NCLOGLEVEL_VERBOSE, 0, 0, 0, 0, 0
  };  
  std::shared_ptr<ncpp::NotCurses> not_curses = std::make_shared<ncpp::NotCurses>();

  eduart::setup_tool::ApplicationMainMenu main_menu(not_curses);

  main_menu.process();
}

void test_software_querier()
{
  eduart::setup_tool::EduArtSoftwareQuerier querier("../../resources/eduart-software-catalog.json");
}

int main(int argc, char** argv)
{
  (void)argc;
  (void)argv;
  // check_root_permission();
  // test_main_menu();
  test_software_querier();

  std::cout << "exit main" << std::endl;
}
