cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snake
	VERSION 0.1.0
	LANGUAGES CXX
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/Version.hpp
)

include(cmake/SetupLibs.cmake)

set(SOURCE
	src/main.cpp
	src/Game/GameContext.cpp
	src/Data/DataManager.cpp
	src/Options/OptionsManager.cpp
	src/Highscores/HighscoreManager.cpp
	src/UI/UIManager.cpp
	src/UI/Gameplay/GameplaySceneUI.cpp
	src/UI/MainMenu/MainMenuSceneUI.cpp
	src/UI/Common/UIButton.cpp
	src/UI/Options/OptionsSceneUI.cpp
	src/UI/Highscores/HighscoresSceneUI.cpp
	src/UI/SaveHighscore/SaveHighscoreSceneUI.cpp
	src/UI/SceneUI.cpp
	src/Scenes/GameplayScene.cpp
	src/Scenes/MainMenuScene.cpp
	src/Scenes/OptionsScene.cpp
	src/Scenes/HighscoresScene.cpp
	src/Scenes/SaveHighscoreScene.cpp
	src/Game/GameState/LoseState.cpp
	src/Game/GameState/PauseState.cpp
	src/Game/GameState/PlayState.cpp
	src/Game/GameState/StartState.cpp
	src/Game/Game.cpp
	src/Game/GameObjects/GameObjects.cpp
	src/Game/GameObjects/Grid.cpp
	src/Game/GameObjects/Snake.cpp
	src/Game/GameObjects/Food.cpp
)

set(HEADERS
	src/Game/GameContext.hpp
	src/Data/DataManager.hpp
	src/Options/OptionsManager.hpp
	src/Highscores/HighscoreManager.hpp
	src/UI/UICommand.hpp
	src/UI/UIManager.hpp
	src/UI/Gameplay/GameplaySceneUI.hpp
	src/UI/MainMenu/MainMenuSceneUI.hpp
	src/UI/Common/UIButton.hpp
	src/UI/Options/OptionsSceneUI.hpp
	src/UI/Highscores/HighscoresSceneUI.hpp
	src/UI/SaveHighscore/SaveHighscoreSceneUI.hpp
	src/UI/SceneUI.hpp
	src/Scenes/Scene.hpp
	src/Scenes/GameplayScene.hpp
	src/Scenes/MainMenuScene.hpp
	src/Scenes/OptionsScene.hpp
	src/Scenes/HighscoresScene.hpp
	src/Scenes/SaveHighscoreScene.hpp
	src/Game/GameState/GameState.hpp
	src/Game/GameState/LoseState.hpp
	src/Game/GameState/PauseState.hpp
	src/Game/GameState/PlayState.hpp
	src/Game/GameState/StartState.hpp
	src/Game/Game.hpp
	src/Game/GameObjects/GameObjects.hpp
	src/Game/GameObjects/Grid.hpp
	src/Game/GameObjects/Snake.hpp
	src/Game/GameObjects/Food.hpp
)

add_executable(snake_app
	${SOURCE}
	${HEADERS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${SOURCE} ${HEADERS})

include(cmake/PostBuild.cmake)

target_link_libraries(snake_app
	PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
		nlohmann_json::nlohmann_json
	PUBLIC
		imgui
)

target_include_directories(snake_app
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
	PUBLIC imgui
)

target_compile_definitions(snake_app PRIVATE
	RES_DIR="${CMAKE_SOURCE_DIR}/res"
)
