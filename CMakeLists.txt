cmake_minimum_required(VERSION 4.2.0)
project(SpaceGame)
set(CMAKE_CXX_STANDARD 17)

#Set internal variables
set (SPACELIB_GAMECLASS_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/private/SpaceLib/lib/GameClass)
set (SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/private/SpaceLib/lib/RendererClass)

#Define the SLD3 library as an imported library
add_library(SDL3 STATIC IMPORTED GLOBAL)
set_target_properties(
  SDL3 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/SDL3/lib/libSDL3.dll.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/SDL3/include
)
#Define SpaceLib as a custom library
add_library(
  SpaceLib STATIC
  #Renderer class source files
  ${SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY}/SpaceLib_Renderer_Constructor.cpp
  ${SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY}/SpaceLib_Renderer_CoordinateGrid.cpp
  ${SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY}/SpaceLib_Renderer_Math.cpp
  ${SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY}/SpaceLib_Renderer_PlanetRendering.cpp
  ${SPACELIB_RENDERERCLASS_SOURCE_DIRECTORY}/SpaceLib_Renderer_ScreenRendering.cpp
  #Game (engine) class source files
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_Background.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_Constructor.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_DeltaTime.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_GameUtils.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_PublicInterface.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_StateMachine.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_InputHandling.cpp
  ${SPACELIB_GAMECLASS_SOURCE_DIRECTORY}/SpaceLib_SpaceGame_Math.cpp
)

#Merge SDL3 with SpaceLib
target_link_libraries(SpaceLib PUBLIC SDL3)
target_include_directories(
  SpaceLib
  PUBLIC ${CMAKE_SOURCE_DIR}/private/SpaceLib/include
)

#Create the executable and link SpaceLib
add_executable(SpaceGame ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(
  SpaceGame
  PRIVATE SpaceLib
)

#Tell the compiler to use grphic interface input instead of launching a console
if (WIN32)
  target_link_options(SpaceGame PRIVATE "-mwindows")
endif()