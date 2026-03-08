#pragma once
#include "Calyx/Core/Base.h"
#include "Calyx/Core/Application.h"

extern Calyx::Application* Calyx::CreateApplication(Calyx::ApplicationCommandLineArgs args);

#ifdef CALYX_PLATFORM_WINDOWS

#ifdef CALYX_DISTRIBUTION
	extern int __argc;
	extern char** __argv;
	int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
	{
		Calyx::Logger::Init();
		auto app = Calyx::CreateApplication({ __argc, __argv });
		app->Run();
		delete app;
	}
#else
	int main(int argc, char** argv)
	{
		Calyx::Logger::Init();
		auto app = Calyx::CreateApplication({ argc, argv });
		app->Run();
		delete app;
	}
#endif

#endif