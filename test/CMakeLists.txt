configure_file(GTestCMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL)
include(GoogleTest)

option(USE_CLANG_TIDY "include clang-tidy warnings in the build log" OFF)
if(USE_CLANG_TIDY)
  find_program(CLANG_TIDY clang-tidy)
endif()

function(add_gtest)
  get_filename_component(test_name ${ARGV0} NAME_WE)
  add_executable(${test_name} ${ARGV})
  target_link_libraries(${test_name} PRIVATE libmatrixloader gtest_main gtest gmock)
  if(USE_CLANG_TIDY)
    set_target_properties(${test_name} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
    set_target_properties(${test_name} PROPERTIES C_CLANG_TIDY "${CLANG_TIDY}")
  endif()

  gtest_discover_tests(${test_name})
endfunction()

add_gtest(parser_tests.cc)
add_gtest(builder_tests.cc)
add_gtest(armadillo.cc)
add_gtest(pressio.cc)

add_executable(example example.cc)
target_link_libraries(example libmatrixloader)
if(USE_CLANG_TIDY)
  set_target_properties(libmatrixloader PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
  set_target_properties(libmatrixloader PROPERTIES C_CLANG_TIDY "${CLANG_TIDY}")
endif()
add_test(test_example example)

