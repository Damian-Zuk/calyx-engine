#pragma once
#include "Calyx/Scripting/GameScript.h"
#include "Calyx/Scripting/ScriptFactory.h"

namespace Calyx {

	class GameScriptDefault : public GameScript
	{
	public:
		GAME_SCRIPT_CLASS(GameScriptDefault);

		GameScriptDefault() = default;
		virtual ~GameScriptDefault() = default;
	};

}