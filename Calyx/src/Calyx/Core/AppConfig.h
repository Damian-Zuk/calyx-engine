#pragma once

namespace Calyx {

	class AppConfig
	{
	public:
		int WindowWidth = 1280;
		int WindowHeight = 720;
		bool Fullscreen = false;
		bool VSync = false;

	public:
		AppConfig() = default;
		virtual ~AppConfig() = default;

		void LoadConfig();
		void WriteConfig();

	private:
		const std::string m_Filepath = "app-config.json";
	};
}

