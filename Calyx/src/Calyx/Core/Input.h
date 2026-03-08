#pragma once

#include "Calyx/Core/KeyCodes.h"

namespace Calyx {

	class EntityScript;

	class Input 
	{
	public:
		static bool IsKeyPressed(int keyCode);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
	};

}
