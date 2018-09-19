cmake_minimum_required (VERSION 3.4)
project(ShaderGen)

FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set(ShaderGen_SRC log.cpp)
set(ShaderGen_TESTS main.cpp)

PREPEND(ShaderGen_SRC src ${ShaderGen_SRC})
PREPEND(ShaderGen_TESTS tests ${ShaderGen_TESTS})

option(BUILD_TESTS "Build the tests" ON)

add_executable(ShaderGen src/main.cpp)
add_executable(ShaderGenTests ${ShaderGen_TESTS})
add_library(ShaderGenCommon SHARED ${ShaderGen_SRC})

target_link_libraries(ShaderGen ShaderGenCommon)
target_link_libraries(ShaderGenTests ShaderGenCommon)

## Dependencies
# Spdlog
target_include_directories(ShaderGenCommon PUBLIC external/spdlog/include)

# Catch
target_include_directories(ShaderGenTests PUBLIC external/Catch2/single_include)

# Boost
find_package(Boost 1.65 REQUIRED COMPONENTS filesystem)
target_include_directories(ShaderGen PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(ShaderGen ${Boost_LIBRARIES})

## Compile Options
set_property(TARGET ShaderGen PROPERTY CXX_STANDARD 17)

if (BUILD_TESTS)
    enable_testing()
    add_test(test ShaderGenTests)
endif()
