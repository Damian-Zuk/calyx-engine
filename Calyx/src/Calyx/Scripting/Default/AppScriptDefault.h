#pragma once
#include "Calyx/Scripting/AppScript.h"
#include "Calyx/Scripting/ScriptFactory.h"

namespace Calyx {

	class AppScriptDefault : public AppScript
	{
	public:
		APP_SCRICX_CLASS(AppScriptDefault);

		AppScriptDefault() = default;
		virtual ~AppScriptDefault() = default;
	};

}