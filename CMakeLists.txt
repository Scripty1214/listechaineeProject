cmake_minimum_required(VERSION 3.13.4)
project(ListeChainee
  VERSION 1.0.1
  LANGUAGES C
)
enable_testing()
add_library(list SHARED list/list.c)
add_library(listStatic STATIC list/list.c)
set_target_properties(listStatic PROPERTIES OUTPUT_NAME list)
set_target_properties(list
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  PUBLIC_HEADER list/list.h)
configure_file(list.pc.in list.pc @ONLY)
target_include_directories(list PRIVATE "${PROJECT_SOURCE_DIR}")
add_executable(listechainee src/listechainee_main.c src/log.c)
set_target_properties(listechainee
  PROPERTIES
  COMPILE_FLAGS "-DDO_LOG")
include_directories(BEFORE "${PROJECT_SOURCE_DIR}")
target_link_libraries(listechainee list)
install(TARGETS list
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/list.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
