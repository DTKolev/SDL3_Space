cmake_minimum_required(VERSION 4.2.0)
project(SpaceGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Fetch SDL3 from GitHub
include(FetchContent)
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
#Set SDL3 properties
set(SDL3_TESTS OFF CACHE INTERNAL "")
set(SDL3_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(SDL3)

#Include the SpaceLib subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/private/SpaceLib)

#Create the executable and link SpaceLib
add_executable(SpaceGame ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(
  SpaceGame
  PRIVATE SpaceLib
)

#Copy SDL3.dll to the bin directory and tell the compiler to use graphic interface input instead of launching a console
if (WIN32)
  add_custom_command(TARGET SpaceGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:SpaceGame>
  )
  target_link_options(SpaceGame PRIVATE "-mwindows")
endif()