#pragma once

#include <unordered_map>
#include <string>
#include <optional>

struct SDL_Window;

namespace options
{
struct Resolution
{
	std::string name;
	int width;
	int height;
};

struct Color
{
	int r{0}, g{0}, b{0}, a{0};
};

class OptionsManager
{
public:
	OptionsManager() = default;
	void setWindow(SDL_Window* window);
	void loadOptions();
	void saveOptions();
	void resetOptions();

	Resolution getCurrentResolution() const;
	std::unordered_map<std::string, Resolution> getResolutionPresets() const;
	void setCurrentResolution(Resolution newResolution);
	void applyCurrentResolution();

	bool getIsFullscreen() const;
	void setIsFullscreen(bool value);

	Color getSnake1Color() const;
	void setSnake1Color(Color color);
	Color getSnake2Color() const;
	void setSnake2Color(Color color);

private:
	void loadOptionPresets();
	void loadUserOptions();

	void centerWindow();

	std::optional<bool> m_isFullscreen;
	bool m_defaultFullscreen;

	std::unordered_map<std::string, Resolution> m_resolutionPresets;
	Resolution m_currentResolution;
	Resolution m_defaultResolution;

	Color m_snake1Color;
	Color m_snake2Color;
	Color m_defaultSnake1Color;
	Color m_defaultSnake2Color;

	SDL_Window* m_window;

	// snake customization options ? (color, starting size, starting direction ?)
	// gameplay options ? (speed, gridsize, cellsize, etc.)
};
}
