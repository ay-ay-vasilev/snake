cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snake
	VERSION 0.1.0
	LANGUAGES CXX
)

include(cmake/SetupLibs.cmake)

set(SOURCE
	src/main.cpp
	src/Constants/Constants.cpp
	src/UI/GameplaySceneUI.cpp
	src/UI/UI.cpp
	src/Scenes/GameplayScene.cpp
	src/Scenes/MainMenuScene.cpp
	src/Scenes/OptionsScene.cpp
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
	src/Constants/Constants.hpp
	src/UI/GameplaySceneUI.hpp
	src/UI/UI.hpp
	src/Scenes/Scene.hpp
	src/Scenes/GameplayScene.hpp
	src/Scenes/MainMenuScene.hpp
	src/Scenes/OptionsScene.hpp
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

include(cmake/PostBuild.cmake)

target_link_libraries(snake_app
	PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
		nlohmann_json::nlohmann_json
	PUBLIC
		imgui
)

target_include_directories(snake_app PUBLIC imgui)
