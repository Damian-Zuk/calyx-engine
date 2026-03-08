#include "cxpch.h"
#include "Calyx/Core/ProjectConfig.h"
#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Utils/Utils.h"
#include "Calyx/Network/Common.h"
#include "Calyx/Scripting/ScriptSerializer.h"
#include "Calyx/Scripting/ScriptFactory.h"

namespace Calyx {

	bool ProjectConfig::LoadConfig()
	{
		if (!std::filesystem::exists(m_Filepath))
		{
			CX_CORE_ERROR("'{}' file not found!", m_Filepath);
			return false;
		}

		json j = j.parse(Utils::ReadFile(m_Filepath));
		if (!j.contains("StartScene"))
		{
			CX_CORE_ERROR("'StartScene' missing in '{}'!", m_Filepath);
			return false;
		}

		StartScene = j["StartScene"];
		AppScript* script = ScriptFactory::Get().AddScriptToGameInstance(Application::GetGameInstance(), j["AppScript"]["ClassName"]);
		ScriptSerializer::DeserializeScript((Script*)script, j);

		return true;
	}

	void ProjectConfig::WriteConfig()
	{
		json jsonObj;
		jsonObj["StartScene"] = StartScene;
		jsonObj["AppScript"] = ScriptSerializer::SerializeScript((Script*)Application::GetGameInstance()->GetAppScript());

		std::ofstream configFile(m_Filepath);
		configFile << jsonObj.dump(4);
		configFile.close();
	}

}
