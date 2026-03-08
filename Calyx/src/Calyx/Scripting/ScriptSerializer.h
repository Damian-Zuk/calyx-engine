#pragma once

namespace Calyx {

	class Script;

	class ScriptSerializer
	{
	public:
		static json SerializeScript(Script* script);
		static void DeserializeScript(Script* script, const json& j);
	};

}
