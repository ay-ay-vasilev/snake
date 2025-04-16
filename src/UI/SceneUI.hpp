#pragma once

#include <SDL3_image/SDL_image.h>

#include <string>
#include <unordered_map>
#include <memory>

#include "UI.hpp"

namespace constants
{
	struct TextData;
}

class ImFont;
namespace ui
{
	struct SceneUIData
	{
		std::pair<int, int> m_windowSize{};
		std::pair<int, int> m_offset{};
		std::unordered_map<std::string, ImFont*> m_fonts;
	};

	struct UIText
	{
		int x;
		int y;
		double scale;
		std::string text;
	};

	void initUIText(const constants::TextData& textData, ui::UIText& uiText);

	class SceneUI : public UI 
	{
	public:
		SceneUI() {}
		virtual ~SceneUI() {}

		virtual void init() override;
		virtual void handleInput(void* appstate, SDL_Event* event) override;
		virtual void update() override;
		virtual void render(SDL_Renderer* renderer, int windowFlags) override;
		void setSceneUIData(std::shared_ptr<SceneUIData> sceneUIData);
	protected:
		std::shared_ptr<SceneUIData> m_sceneUIData;
	};
}
