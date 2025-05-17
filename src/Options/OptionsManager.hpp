#pragma once

#include <vector>
#include <string>

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
	void loadOptions();
	void saveOptions();

	Resolution getCurrentResolution() const;
	std::vector<Resolution> getResolutionPresets() const;

private:
	void loadOptionPresets();
	void loadUserOptions();

	std::vector<Resolution> m_resolutionPresets;
	Resolution m_currentResolution;
	bool m_isFullscreen;

	// snake customization options ? (color, starting size, starting direction ?)
	// gameplay options ? (speed, gridsize, cellsize, etc.)
};
}
