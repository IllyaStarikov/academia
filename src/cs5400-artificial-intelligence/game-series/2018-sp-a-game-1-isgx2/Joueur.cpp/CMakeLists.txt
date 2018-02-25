if(CMAKE_MAJOR_VERSION LESS 3)
   cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
elseif()
   cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
endif()

# set explicity policies
if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
   cmake_policy(SET CMP0054 NEW)
endif(COMMAND cmake_policy)

get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

#prevent in-source build
if("${srcdir}" STREQUAL "${bindir}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif()

project(cpp-client)

#set files before adding subdirectories
set(FILES "")

#for generated file dependencies
add_custom_target(dependencies ALL)

#find generated files
add_subdirectory(games)

add_executable(cpp-client ${FILES}
                          joueur/src/any.hpp
                          joueur/src/attr_wrapper.hpp
                          joueur/src/base_ai.cpp
                          joueur/src/base_ai.hpp
                          joueur/src/base_game.hpp
                          joueur/src/base_game.cpp
                          joueur/src/base_object.cpp
                          joueur/src/base_object.hpp
                          joueur/src/connection.cpp
                          joueur/src/connection.hpp
                          joueur/src/delta.cpp
                          joueur/src/delta.hpp
                          joueur/src/delta_mergable.cpp
                          joueur/src/delta_mergable.hpp
                          joueur/src/exceptions.hpp
                          joueur/src/main.cpp
                          joueur/src/register.cpp
                          joueur/src/register.hpp
                          joueur/src/sgr.hpp)

add_dependencies(cpp-client dependencies)

#include library files
include_directories(cpp-client "joueur/libraries/tclap/include/"
                               "joueur/libraries/rapidjson/include/")

if(WIN32 OR MSYS)
   target_link_libraries(cpp-client ws2_32)
endif(WIN32 OR MSYS)

# Warnings
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
   set_target_properties(cpp-client PROPERTIES COMPILE_OPTIONS
                         "-Wall" "-Wextra" "-pedantic")
elseif("$CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
   set_target_properties(cpp-client PROPERTIES COMPILE_OPTIONS
                         "/W4")
endif()

#set C++11
if(CMAKE_MAJOR_VERSION LESS 3)
   if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR
      "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
      set_target_properties(cpp-client PROPERTIES COMPILE_OPTIONS "-std=c++11")
   endif()
else()
   set_target_properties(cpp-client PROPERTIES CXX_STANDARD 11)
   set_target_properties(cpp-client PROPERTIES CXX_STANDARD_REQUIRED ON)
endif()
