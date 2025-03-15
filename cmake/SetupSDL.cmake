# Detect platform and set SDL3 path
if(WIN32)
	set(SDL3_PATH "${CMAKE_SOURCE_DIR}/libs/windows/SDL")
	set(SDL3IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/windows/SDL_image")
elseif(APPLE)
	set(SDL3_PATH "${CMAKE_SOURCE_DIR}/libs/windows/SDL")
	set(SDL3IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/windows/SDL_image")
elseif(UNIX)
	set(SDL3_PATH "${CMAKE_SOURCE_DIR}/libs/linux/SDL")
	set(SDL3IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/linux/SDL_image")
endif()

# Set CMake prefix path for SDL3
list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}" "${SDL3IMAGE_PATH}")

# Find SDL3
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)