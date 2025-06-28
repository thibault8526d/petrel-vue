cmake_minimum_required(VERSION 3.10)
project(myjpgplugin)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenCPN REQUIRED)

add_subdirectory(src)
install(FILES plugin.xml DESTINATION share/opencpn/plugins/myjpgplugin)
install(DIRECTORY data DESTINATION share/opencpn/plugins/myjpgplugin)
