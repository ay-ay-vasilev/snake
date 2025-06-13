#pragma once

#include <vector>
#include <string>

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

	Resolution getCurrentResolution() const;
	std::vector<Resolution> getResolutionPresets() const;
	void setCurrentResolution(Resolution newResolution);
	void applyCurrentResolution();

private:
	void loadOptionPresets();
	void loadUserOptions();

	void centerWindow();


	std::vector<Resolution> m_resolutionPresets;
	Resolution m_currentResolution;
	bool m_isFullscreen;
	SDL_Window* m_window;

	// snake customization options ? (color, starting size, starting direction ?)
	// gameplay options ? (speed, gridsize, cellsize, etc.)
};
}
