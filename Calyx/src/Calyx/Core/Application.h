#pragma once

#include "Calyx/Core/Base.h"
#include "Calyx/Core/AppConfig.h"
#include "Calyx/Core/LayerStack.h"
#include "Calyx/Core/Window.h"

#ifdef CALYX_PLATFORM_WINDOWS
	#ifdef CALYX_DISTRIBUTION
		int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);
	#else
		int main(int argc, char** argv);
	#endif
#else
	int main(int argc, char** argv);
#endif


namespace Calyx {

	// Forward declaration
	class GameInstance;

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			CX_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Calyx Engine";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application() = default;

		static Application& Get() { return *s_Instance; }

		void Run();
		void Exit();

		float GetTimeScale() const { return m_TimeScale; };
		float GetLastFrameTime() { return s_Instance->m_FrameTime; }
		float GetTotalTimeElapsed();

		Window& GetWindow() { return *m_Window; }
		const Window& GetWindow() const { return *m_Window; }
		static GameInstance* GetGameInstance();

	protected:
		void OnEvent(Event& event);

	private:
		static Application* s_Instance;
#ifndef CX_EDITOR
		Unique<GameInstance> m_GameInstance;
#endif
		Unique<Window> m_Window;

		ApplicationSpecification m_Specification;
		AppConfig m_AppConfig;
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
		bool m_WindowMinimized = false;
		float m_FrameTime = 0.0f;
		float m_TimeScale = 1.0f;

		friend class SettingsPanel;
		friend class InfoPanel;
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);

}