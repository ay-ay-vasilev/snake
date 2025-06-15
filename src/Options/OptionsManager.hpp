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

private:
	void loadOptionPresets();
	void loadUserOptions();

	void centerWindow();

	std::optional<bool> m_isFullscreen;
	bool m_defaultFullscreen;
	std::unordered_map<std::string, Resolution> m_resolutionPresets;
	Resolution m_currentResolution;
	Resolution m_defaultResolution;
	SDL_Window* m_window;

	// snake customization options ? (color, starting size, starting direction ?)
	// gameplay options ? (speed, gridsize, cellsize, etc.)
};
}
