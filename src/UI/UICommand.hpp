#pragma once

#include <any>

namespace ui
{
	enum class eUICommandType
	{
		ChangeScene,
		ChangeState, // ???
		QuitGame
	};

	struct UICommand
	{
		eUICommandType type;
		std::any value;
	};
}
