cmake_minimum_required(VERSION 3.12)
project(libmatrixloader VERSION "0.0.1" LANGUAGES CXX)

#correct was to set a default build type
# https://blog.kitware.com/cmake-and-the-default-build-type/
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type was set. Setting build type to ${default_build_type}.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE 
    STRING "Choose the type to build" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

include(CTest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)
option(BUILD_SHARED_LIBS "Prefer building shared libraries" ON)

add_library(libmatrixloader 
  src/empty.cc
  )

target_include_directories(
  libmatrixloader
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/libmatrixloader>
  )
list(APPEND libmatrixloader_targets libmatrixloader)

option(LIBMATRIXLOADER_HAS_ARMADILLO "libmatrixloader has Armadillo" OFF)
if(LIBMATRIXLOADER_HAS_ARMADILLO)
  find_package(Armadillo)
  target_link_libraries(libmatrixloader PUBLIC ${ARMADILLO_LIBRARIES})
  target_include_directories(libmatrixloader PUBLIC ${ARMADILLO_INCLUDE_DIRS})
endif()


option(LIBMATRIXLOADER_HAS_LIBPRESSIO "libmatrixloader has LibPressio" OFF)
if(LIBMATRIXLOADER_HAS_LIBPRESSIO)
  find_package(LibPressio)
  target_link_libraries(libmatrixloader PUBLIC LibPressio::libpressio)
endif()


configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/matrixloader_config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/matrixloader_config.h
  )



export(TARGETS ${libmatrixloader_targets} NAMESPACE libmatrixloader:: FILE
  LibMatrixloaderConfig.cmake)
install(TARGETS ${libmatrixloader_targets} EXPORT LibMatrixloaderConfig
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmatrixloader
  )
install(EXPORT LibMatrixloaderConfig NAMESPACE libmatrixloader:: DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/libmatrixloader/cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/matrixloader_config.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmatrixloader)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libmatrixloader)

option(BUILD_DOCS "build the documetation" OFF)
if(BUILD_DOCS)
  find_package(Doxygen REQUIRED dot)
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_MAN_LINKS YES)
  set(DOXYGEN_GENERATE_MAN YES)
  set(DOXYGEN_EXTRACT_LOCAL_METHODS YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_MACRO_EXPANSION YES)
  set(DOXYGEN_EXCLUDE_PATTERNS "*_impl.h")
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
  doxygen_add_docs(
    docs
    ${PROJECT_SOURCE_DIR}/README.md
    ${PROJECT_SOURCE_DIR}/include
    COMMENT "Generate Documenation"
  )
endif()

if(BUILD_TESTING)
  add_subdirectory(test)
endif()


