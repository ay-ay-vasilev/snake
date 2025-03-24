cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(snake
	VERSION 0.1.0
	LANGUAGES CXX
)

include(cmake/SetupLibs.cmake)

add_executable(snake_app
	src/main.cpp
	src/Constants/Constants.cpp
	src/UI/UI.cpp
	src/Game/GameState/GameState.cpp
	src/Game/GameState/LoseState.cpp
	src/Game/GameState/PauseState.cpp
	src/Game/GameState/PlayState.cpp
	src/Game/GameState/StartState.cpp
	src/Game/Game.cpp
	src/Game/Grid.cpp
	src/Game/Snake.cpp
)

include(cmake/PostBuild.cmake)

target_link_libraries(snake_app
	PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
		nlohmann_json::nlohmann_json
)