#include "UI.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "../Constants/Constants.hpp"

#include <iostream>

void initUIText(const constants::TextData& textData, ui::UIText& uiText)
{
	uiText.x = textData.x;
	uiText.y = textData.y;
	uiText.scale = textData.scale;
}

void ui::UI::init(SDL_Window* window, SDL_Renderer* renderer)
{
	auto& dataManager = constants::DataManager::getInstance();

	const auto& scoreTextData = dataManager.getConstant<constants::TextData>("score_text");
	const auto& gameStateTextData = dataManager.getConstant<constants::TextData>("game_state_text");
	const auto& debugTextData = dataManager.getConstant<constants::TextData>("debug_text");

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

	initUIText(scoreTextData, m_scoreText);
	initUIText(gameStateTextData, m_gameStateText);
	initUIText(debugTextData, m_debugText);

	m_offset = offset;
	m_windowSize = {windowWidth, windowHeight};
	m_scoreText.text = "Score: " + std::to_string(m_score);
	m_gameStateText.text = "START";
	m_debugText.text = "DEBUG";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	const auto fileName = "../res/fonts/romulus.ttf";
	regularFont = io.Fonts->AddFontFromFileTTF(fileName, 45.0f);
	ImGui::GetIO().Fonts->Build();
}

void ui::UI::handleInput(void* appstate, SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

void ui::UI::update()
{
	m_scoreText.text = "Score: " + std::to_string(m_score);
}

void ui::UI::preRender(SDL_Renderer* renderer)
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();

	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(m_windowSize.first, m_windowSize.second), ImGuiCond_Always);

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

	ImGui::Begin("Snake", NULL, window_flags); // game screen window

	ImGui::PushFont(regularFont);
	const auto scoreText = m_scoreText.text.c_str();
	ImGui::SetCursorPosX(m_offset.first);
	ImGui::Text("%s", scoreText);

	const auto gameStateText = m_gameStateText.text.c_str();
	ImGui::SetCursorPosX(m_offset.first);
	ImGui::Text("%s", gameStateText);
	ImGui::PopFont();

	ImGui::End();

	// Rendering
	ImGui::Render();
	//SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColorFloat(renderer, 0.f, 0.f, 0.f, 1.f);
	SDL_RenderClear(renderer);
}

void ui::UI::postRender(SDL_Renderer* renderer)
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);

	renderUIText(renderer, m_scoreText);
	renderUIText(renderer, m_gameStateText);
	renderUIText(renderer, m_debugText);
}

void ui::UI::shutdown()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ui::UI::addScore(int value)
{
	m_score += value;
}

void ui::UI::setGameStateText(const std::string_view& text)
{
	m_gameStateText.text = text;
}

void ui::UI::setDebugText(const std::string_view& text)
{
	m_debugText.text = text;
}

void ui::UI::getNotified(const ObserverMessage& message)
{
	switch (message.m_type)
	{
	case ObserverMessageType::eScore:
		addScore(std::any_cast<int>(message.m_value));
		break;
	case ObserverMessageType::eGameState:
		m_gameStateText.text = std::any_cast<std::string>(message.m_value);
		break;
	default:
		break;
	}
}

void ui::UI::renderUIText(SDL_Renderer* renderer, const UIText& uiText)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, uiText.scale, uiText.scale);
	SDL_RenderDebugText(renderer,
		(uiText.x + m_offset.first) / uiText.scale,
		(uiText.y + m_offset.second) / uiText.scale,
		uiText.text.c_str());
	SDL_SetRenderScale(renderer, 1.f, 1.f);
}