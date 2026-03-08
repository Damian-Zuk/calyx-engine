#include "cxpch.h"
#ifdef CX_EDITOR
#include "Calyx/Editor/EditorConfig.h"
#include "Calyx/Utils/Utils.h"

namespace Calyx {

	void EditorConfig::LoadConfig()
	{
		EditorFonts.clear();

		if (!std::filesystem::exists(m_Filepath))
		{
			CX_CORE_WARN("'{}' file not found! Creating config with default values.", m_Filepath);
			EditorFonts.insert(std::pair("roboto", Font{ "editor/content/font/Roboto.ttf", 18.0f }));
			WriteConfig();
			return;
		}

		json jsonObj = jsonObj.parse(Utils::ReadFile(m_Filepath));
		for (const auto& font : jsonObj["Fonts"].items())
			EditorFonts.insert(std::pair(font.key(), Font{ font.value()["FontFilepath"], font.value()["FontSize"] }));
	}

	void EditorConfig::WriteConfig()
	{
		json jsonObj;
		for (const auto& [fontName, font] : EditorFonts)
		{
			jsonObj["Fonts"][fontName] = {
				{ "FontFilepath", font.FontFilepath },
				{ "FontSize", font.FontSize }
			};
		}
		std::ofstream configFile(m_Filepath);
		configFile << jsonObj.dump(4);
		configFile.close();
	}
}

#endif
