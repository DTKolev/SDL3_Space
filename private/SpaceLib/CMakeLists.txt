add_library(SpaceLib STATIC
  #Engine source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Engine/SpaceLib_GameClass_Input.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Engine/SpaceLib_GameClass_PublicInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Engine/SpaceLib_GameClass_StateMachine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Engine/SpaceLib_Renderer.cpp
  #Game states source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_States/SpaceLib_DeathScreen.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_States/SpaceLib_GameScreen.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_States/SpaceLib_MainMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_States/SpaceLib_PauseMenu.cpp
  #Game utils source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_Utils/SpaceLib_PlanetManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Game_Utils/SpaceLib_Utils.cpp
  #Visual elements source files
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_Background.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_GameTitle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_HomeButton.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_PlayButton.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_ScreenButton_Parent.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Visual_Elements/SpaceLib_Title_Parent.cpp
  #Header files
  ${CMAKE_CURRENT_SOURCE_DIR}/include/SpaceHeader.hpp
)

target_include_directories(SpaceLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(SpaceLib PUBLIC SDL3::SDL3)