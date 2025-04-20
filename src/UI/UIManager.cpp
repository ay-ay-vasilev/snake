#include "UIManager.hpp"

#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "SceneUI.hpp"
#include "../Constants/Constants.hpp"

void ui::UIManager::init(SDL_Window* window, SDL_Renderer* renderer)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	auto& dataManager = constants::DataManager::getInstance();

	const auto windowWidth = dataManager.getConstant<int>("window_width");
	const auto windowHeight = dataManager.getConstant<int>("window_height");
	const auto gridWH = dataManager.getConstant<int>("grid_size");
	const auto cellWH = dataManager.getConstant<int>("cell_size");

	const auto gridWidth = gridWH * cellWH;
	const auto gridHeight = gridWH * cellWH;
	const std::pair<int, int> offset =
		{
			(windowWidth - gridWidth) / 2,
			(windowHeight - gridHeight) / 2
		};
	
	m_sceneUIData = std::make_shared<SceneUIData>();
	m_sceneUIData->m_offset = offset;
	m_sceneUIData->m_windowSize = {windowWidth, windowHeight};

	const auto fileName = "../res/fonts/romulus.ttf";
	auto smallFont = io.Fonts->AddFontFromFileTTF(fileName, 20.0f);
	auto regularFont = io.Fonts->AddFontFromFileTTF(fileName, 60.0f);
	auto bigFont = io.Fonts->AddFontFromFileTTF(fileName, 120.0f);
	m_sceneUIData->m_fonts["small_font"] = smallFont;
	m_sceneUIData->m_fonts["regular_font"] = regularFont;
	m_sceneUIData->m_fonts["big_font"] = bigFont;
	ImGui::GetIO().Fonts->Build();
}

void ui::UIManager::handleInput(void* appstate, SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
	m_sceneUI->handleInput(appstate, event);
}

void ui::UIManager::update()
{
	m_sceneUI->update();
}

void ui::UIManager::preRender(SDL_Renderer* renderer)
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();

	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(m_sceneUIData->m_windowSize.first, m_sceneUIData->m_windowSize.second), ImGuiCond_Always);

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	m_sceneUI->render(renderer, window_flags);

	//ImGui::Begin("Test", NULL, static_cast<ImGuiWindowFlags>(window_flags)); // game screen window
	//ImGui::ShowDemoWindow();
	//ImGui::End();

	// Rendering
	ImGui::Render();
	//SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColorFloat(renderer, 0.f, 0.f, 0.f, 1.f);
	SDL_RenderClear(renderer);

}

void ui::UIManager::postRender(SDL_Renderer* renderer)
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);
}

void ui::UIManager::shutdown()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ui::UIManager::setSceneUI(std::shared_ptr<ui::SceneUI> sceneUI)
{
	m_sceneUI = sceneUI;
	m_sceneUI->setSceneUIData(m_sceneUIData);
	m_sceneUI->setCommandCallback([this](UICommand command)
							   {
							   m_commandQueue.push(std::move(command));
							   });
}

void ui::UIManager::pushCommand(const ui::UICommand& command)
{
	m_commandQueue.push(command);
}

std::optional<ui::UICommand> ui::UIManager::pollCommand()
{
	if (m_commandQueue.empty())
		return std::nullopt;

	auto command = m_commandQueue.front();
	m_commandQueue.pop();
	return command;
}
