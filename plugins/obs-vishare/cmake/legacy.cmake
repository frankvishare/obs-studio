project(obs-vishare)

option(ENABLE_VISHARE "Enable Vishare Output support" ON)
if(NOT ENABLE_VISHARE)
  obs_status(DISABLED "obs-vishare")
  return()
endif()

find_package(LibDataChannel 0.20 REQUIRED)
find_package(CURL REQUIRED)

add_library(obs-vishare MODULE)
add_library(OBS::vishare ALIAS obs-vishare)

target_sources(obs-vishare PRIVATE obs-vishare.cpp vishare-output.cpp vishare-output.h vishare-service.cpp vishare-service.h
                                  vishare-utils.h)

target_link_libraries(obs-vishare PRIVATE OBS::libobs LibDataChannel::LibDataChannel CURL::libcurl)

set_target_properties(obs-vishare PROPERTIES FOLDER "plugins")

setup_plugin_target(obs-vishare)
