add_library(picosys_c INTERFACE)

target_sources(picosys_c INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/picosys_c.cpp
)

target_include_directories(picosys_c INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(picosys_c INTERFACE picosystem)
