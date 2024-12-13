cmake_minimum_required(VERSION 3.8)
project(eduart_setup_tool)

find_package(Notcurses REQUIRED)
find_package(Notcurses++ REQUIRED)

add_subdirectory(src)
