#include "cxpch.h"
#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Core/Timer.h"
#include "Calyx/Core/Input.h"
#include "Calyx/Core/AssetManager.h"

#include "Calyx/Events/WindowEvents.h" 
#include "Calyx/Events/KeyEvents.h"
#include "Calyx/Events/MouseEvents.h"

#include "Calyx/Graphics/Renderer/Renderer.h"
#include "Calyx/Scene/SceneManager.h"
#include "Calyx/Scene/PrefabManager.h"
#include "Calyx/Scripting/GameScript.h"

#ifdef CALYX_PLATFORM_WINDOWS
#include "Calyx/Platform/Windows/WindowsWindow.h"
#endif

#ifdef CX_EDITOR
#include "Calyx/Editor/EditorLayer.h"
#include "Calyx/Editor/Panels/SceneViewportPanel.h"
#include "Calyx/Editor/Menu/EditorMenuBar.h"
#endif

namespace Calyx {

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		CX_CORE_ASSERT(!s_Instance, "Application already exists!");
		Application::s_Instance = this;

		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_AppConfig.LoadConfig();

		WindowSpecification windowSpec;
		windowSpec.Title = m_Specification.Name;
		windowSpec.Width = m_AppConfig.WindowWidth;
		windowSpec.Height = m_AppConfig.WindowHeight;
		windowSpec.Fullscreen = m_AppConfig.Fullscreen;
		windowSpec.VSync = m_AppConfig.VSync;

#ifdef CALYX_PLATFORM_WINDOWS
		m_Window = MakeUnique<WindowsWindow>(windowSpec);
#endif
		m_Window->SetEventCallback(CX_BIND_FUNCTION(Application::OnEvent));

		AssetManager::Init();
		PrefabManager::Init();
		Renderer::Init();
	}

	void Application::Run()
	{
		if (m_IsRunning)
		{
			CX_CORE_ERROR("Application is already running!");
			return;
		}

		m_IsRunning = true;

#ifdef CX_EDITOR
		EditorLayer* editorLayer = m_LayerStack.PushOverlay<EditorLayer>();
#else
		m_GameInstance = MakeUnique<GameInstance>();
		m_GameInstance->Init();
		Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
#endif

		PROFILE_BEGIN_SESSION("Calyx-Runtime");
		PROFILE_SCOPE("app_game_loop");

		// Main loop
		while (m_IsRunning) 
		{
			Timer timer;

			if (!m_WindowMinimized) 
			{
			{
				PROFILE_SCOPE("app_layers_update");
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(m_FrameTime * m_TimeScale);
				}
			}

#ifdef CX_EDITOR
			{
				PROFILE_SCOPE("imgui_render");
				editorLayer->BeginImGuiRender();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				editorLayer->EndImGuiRender();
			}
#else
				m_GameInstance->OnUpdate(m_FrameTime * m_TimeScale);
#endif
			}

			m_Window->OnUpdate();
			m_FrameTime = timer.Elapsed();
		}

		Renderer::Shutdown();
		PROFILE_END_SESSION();
	}

	GameInstance* Application::GetGameInstance()
	{
#ifdef CX_EDITOR
		return EditorLayer::GetMainGameInstance();
#else
		return m_GameInstance.get();
#endif
	}

	void Application::Exit()
	{
		m_IsRunning = false;
	}

	static Timer s_AppTimer;
	float Application::GetTotalTimeElapsed()
	{
		return s_AppTimer.Elapsed();
	}	

	void Application::OnEvent(Event& event)
	{
		PROFILE_FUNCTION();
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<KeyPressedEvent>([&](KeyPressedEvent& e)
		{
			if (e.GetKeyCode() == Key::F11)
				m_Window->SetFullscreen(!m_Window->IsFullscreen());
			return false;
		});

		dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& e)
		{
			Exit();
			return true;
		});

#ifdef CALYX_DISTRIBUTION
		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent& e)
		{
			uint32_t width = e.GetWidth(), height = e.GetHeight();
			if (width && height)
			{
				m_WindowMinimized = false;
				Renderer::SetViewport(0, 0, width, height);

				for (auto& kv : m_GameInstance->GetSceneManager()->m_Scenes)
					kv.second->OnViewportResize(width, height);
			}
			else 
				m_WindowMinimized = true;

			return false;
		});
#endif

		for (Layer* layer : m_LayerStack)
		{
			if (event.Handled)
				return;

			layer->OnEvent(event);
		}

		if (event.Handled)
			return;

#ifdef CX_EDITOR
		Scene* scene = EditorLayer::GetFocusedGameInstance()->GetActiveScene();
#else
		Scene* scene = m_GameInstance->GetActiveScene();
#endif 

		if (scene && scene->IsSimulated())
			scene->GetGameScript()->OnEvent(event);
	}

}
