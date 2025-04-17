#pragma once

#include <SDL3_image/SDL_image.h>

#include "../Abstract/Observer.hpp"
#include "UICommand.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

namespace constants
{
	struct TextData;
}

class ImFont;
namespace ui
{
	struct SceneUIData // todo: rethink
	{
		std::pair<int, int> m_windowSize{};
		std::pair<int, int> m_offset{};
		std::unordered_map<std::string, ImFont*> m_fonts;
	};

	struct UIText // todo: utilize better
	{
		int x;
		int y;
		double scale;
		std::string text;
	};

	void initUIText(const constants::TextData& textData, ui::UIText& uiText);

	class SceneUI : public IObserver 
	{
	public:
		SceneUI() {}
		virtual ~SceneUI() {}

		virtual void init() = 0;
		virtual void handleInput(void* appstate, SDL_Event* event) = 0;
		virtual void update() = 0;
		virtual void render(SDL_Renderer* renderer, int windowFlags) = 0;
		void setSceneUIData(std::shared_ptr<SceneUIData> sceneUIData);
		void setCommandCallback(std::function<void(UICommand)> callback);
	protected:
		std::shared_ptr<SceneUIData> m_sceneUIData;
		std::function<void(UICommand)> m_commandCallback;
	};
}
