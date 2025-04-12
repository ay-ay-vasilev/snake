#include "GameplaySceneUI.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "../Constants/Constants.hpp"

#include <iostream>

void ui::GameplaySceneUI::init(SDL_Window* window, SDL_Renderer* renderer)
{
	UI::init(window, renderer);

	auto& dataManager = constants::DataManager::getInstance();
	
	const auto& scoreTextData = dataManager.getConstant<constants::TextData>("score_text");
	const auto& gameStateTextData = dataManager.getConstant<constants::TextData>("game_state_text");
	const auto& debugTextData = dataManager.getConstant<constants::TextData>("debug_text");

	ui::initUIText(scoreTextData, m_scoreText);
	ui::initUIText(gameStateTextData, m_gameStateText);
	ui::initUIText(debugTextData, m_debugText);

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

void ui::GameplaySceneUI::handleInput(void* appstate, SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

void ui::GameplaySceneUI::update()
{
	m_scoreText.text = "Score: " + std::to_string(m_score);
}

void ui::GameplaySceneUI::preRender(SDL_Renderer* renderer)
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

void ui::GameplaySceneUI::postRender(SDL_Renderer* renderer)
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);

	renderUIText(renderer, m_scoreText);
	renderUIText(renderer, m_gameStateText);
	renderUIText(renderer, m_debugText);
}

void ui::GameplaySceneUI::shutdown()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ui::GameplaySceneUI::addScore(int value)
{
	m_score += value;
}

void ui::GameplaySceneUI::clearScore()
{
	m_score = 0;
}

void ui::GameplaySceneUI::setGameStateText(const std::string_view& text)
{
	m_gameStateText.text = text;
}

void ui::GameplaySceneUI::setDebugText(const std::string_view& text)
{
	m_debugText.text = text;
}

void ui::GameplaySceneUI::getNotified(const ObserverMessage& message)
{
	switch (message.m_type)
	{
	case ObserverMessageType::eAddScore:
		addScore(std::any_cast<int>(message.m_value));
		break;
	case ObserverMessageType::eClearScore:
		clearScore();
		break;
	case ObserverMessageType::eGameState:
		m_gameStateText.text = std::any_cast<std::string>(message.m_value);
		break;
	default:
		break;
	}
}
