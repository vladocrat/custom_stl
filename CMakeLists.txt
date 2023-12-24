cmake_minimum_required(VERSION 3.5)

project(custom_stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(custom_stl main.cpp
    utils.h
    vector.h vector.cpp
    iterator.h
)

include(GNUInstallDirs)
install(TARGETS custom_stl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
