set(SDL3_PATH "${CMAKE_SOURCE_DIR}/libs/SDL")
set(SDL3IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/SDL_image")

# Set CMake prefix path for SDL3
list(APPEND CMAKE_PREFIX_PATH "${SDL3_PATH}" "${SDL3IMAGE_PATH}")

# Find SDL3
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)