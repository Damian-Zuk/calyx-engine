#pragma once

namespace Calyx {

	class Script;

	class ScriptEditWidget
	{
	public:
		ScriptEditWidget() = default;
		virtual ~ScriptEditWidget() = default;

		static void DrawFieldEdit(Script* script);

	};

}

