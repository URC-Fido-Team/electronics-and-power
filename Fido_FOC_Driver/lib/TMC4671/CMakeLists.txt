add_library(TMC4671 INTERFACE)

target_sources(TMC4671 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/TMC4671.c
)

target_include_directories(TMC4671 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
#  target_link_libraries(NTP_Client INTERFACE pico_stdlib)