add_library(SpaceLib STATIC
  #Renderer class source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/RendererClass/SpaceLib_Renderer_Constructor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/RendererClass/SpaceLib_Renderer_CoordinateGrid.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/RendererClass/SpaceLib_Renderer_Math.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/RendererClass/SpaceLib_Renderer_PlanetRendering.cpp
  #Game (engine) class source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_ElementRendering.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_DeltaTime.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_GameUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_PublicInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_StateMachine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_InputHandling.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_Math.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/GameClass/SpaceLib_SpaceGame_ScreenRendering.cpp
  #Header files
  ${CMAKE_CURRENT_SOURCE_DIR}/include/SpaceHeader.hpp
)

target_include_directories(SpaceLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(SpaceLib PUBLIC SDL3::SDL3)