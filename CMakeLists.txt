cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

project(snake
	VERSION 0.1.0
	LANGUAGES CXX
)

include(cmake/SetupSDL.cmake)

add_executable(snake_app
	src/main.cpp
	src/Game/Game.cpp
	src/Game/Grid.cpp
	src/Game/UI.cpp
)

include(cmake/PostBuild.cmake)

target_link_libraries(snake_app
	PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
)