include(cmake/SetupSDL.cmake)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(IMGUI_PATH libs/imgui)
file(GLOB IMGUI_GLOB
	${IMGUI_PATH}/imgui.h
	${IMGUI_PATH}/imgui.cpp
	${IMGUI_PATH}/imconfig.h
	${IMGUI_PATH}/imgui_demo.cpp
	${IMGUI_PATH}/imgui_draw.cpp
	${IMGUI_PATH}/imgui_internal.h
	${IMGUI_PATH}/imstb_rectpack.h
	${IMGUI_PATH}/imstb_textedit.h
	${IMGUI_PATH}/imstb_truetype.h
	${IMGUI_PATH}/imgui_tables.cpp
	${IMGUI_PATH}/imgui_widgets.cpp
	${IMGUI_PATH}/misc/cpp/imgui_stdlib.cpp

	# specific bindings...
	${IMGUI_PATH}/backends/imgui_impl_sdl3.h
	${IMGUI_PATH}/backends/imgui_impl_sdl3.cpp
	${IMGUI_PATH}/backends/imgui_impl_sdlrenderer3.h
	${IMGUI_PATH}/backends/imgui_impl_sdlrenderer3.cpp)
add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE SDL3::SDL3)
