#include <ncpp/CellStyle.hh>
#include <ncpp/NotCurses.hh>

#include <iostream>

int main(int argc, char** argv)
{
  ncpp::NotCurses not_curses;

  const ncpp::CellStyle style = not_curses.get_supported_styles();
  auto plane = not_curses.get_stdplane();

  const std::uint64_t left_color = 0xff0000;
  const std::uint64_t right_color = 0x00ff00;

  const int ret = plane->gradient(5, 5, 30, 30, "test", NCSTYLE_BOLD, left_color, right_color, left_color, right_color);

  not_curses.render();
  std::cerr << "ret = " << ret << std::endl;
}
