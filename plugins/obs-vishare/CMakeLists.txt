cmake_minimum_required(VERSION 3.22...3.25)

legacy_check()

option(ENABLE_VISHARE "Enable Vishare Output support" ON)
if(NOT ENABLE_VISHARE)
  target_disable(obs-vishare)
  return()
endif()

find_package(LibDataChannel 0.20 REQUIRED)
find_package(CURL REQUIRED)

add_library(obs-vishare MODULE)
add_library(OBS::vishare ALIAS obs-vishare)

target_sources(
  obs-vishare PRIVATE # cmake-format: sortable
                     obs-vishare.cpp vishare-output.cpp vishare-output.h vishare-service.cpp vishare-service.h vishare-utils.h)

target_link_libraries(obs-vishare PRIVATE OBS::libobs LibDataChannel::LibDataChannel CURL::libcurl)

# cmake-format: off
set_target_properties_obs(obs-vishare PROPERTIES FOLDER plugins PREFIX "")
# cmake-format: on
