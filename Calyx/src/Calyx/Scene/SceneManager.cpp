#include "cxpch.h"
#include "Calyx/Scene/SceneManager.h"
#include "Calyx/Scene/Scene.h"
#include "Calyx/Scene/SceneSerializer.h"
#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Graphics/Renderer/Renderer.h"

#ifdef CX_EDITOR
#include "Calyx/Editor/EditorLayer.h"
#include "Calyx/Editor/Panels/SceneViewportPanel.h"
#endif

namespace Calyx {

	SceneManager::SceneManager(GameInstance* gameInstance)
		: m_GameInstance(gameInstance)
	{
	}

	void SceneManager::OnUpdate(float ts)
	{
		m_ActiveScene->OnUpdate(ts);
	}

	Scene* SceneManager::GetScene(const std::string& scenePath)
	{
		return m_Scenes.at(scenePath).get();
	}

	Scene* SceneManager::GetActiveScene()
	{
		return m_ActiveScene;
	}

	Scene* SceneManager::SetActiveScene(const std::string& scenePath)
	{
		if (!IsLoaded(scenePath))
		{
			if (!Load(scenePath))
			{
				CX_CORE_ERROR("Scene '{}' not loaded!", scenePath);
				return nullptr;
			}
		}
		
		Scene* scene = GetScene(scenePath);
		SetActiveScene(scene);

		return m_ActiveScene;
	}

	Scene* SceneManager::SetActiveScene(Scene* scene)
	{
		m_ActiveScene = scene;

#ifdef CX_EDITOR
		const auto& viewport = m_GameInstance->m_EditorGameInstance->Viewport;
		viewport->SetActiveScene(scene, true);
#endif

		if (scene)
		{
			Renderer::SetClearColor(m_ActiveScene->m_ClearColor);
		}
		return scene;
	}

	Scene* SceneManager::Load(const std::string& scenePath)
	{
		//CX_CORE_INFO("file='{}.scene.json'", scenePath);
		auto scene = MakeShared<Scene>(m_GameInstance, scenePath);
		SceneSerializer serializer(scene.get());
		scene->m_GameInstance = m_GameInstance;

		std::string filepath = "content/scenes/" + scenePath + ".scene.json";
		if (!serializer.DeserializeSceneFromFile(filepath))
		{
			CX_CORE_ERROR("Loading '{}' failed!", filepath);
			return nullptr;
		}
		m_Scenes[scenePath] = scene;
		return scene.get();
	}

	void SceneManager::Unload(const std::string& scenePath)
	{
		Scene* scene = GetScene(scenePath);
		if (!scene)
		{
			CX_CORE_ERROR("scene='{}' not found", scenePath);
			return;
		}

		CX_CORE_INFO("scene='{}'", scenePath);
		bool active = scene == m_ActiveScene;
		m_Scenes.erase(scenePath);

		if (active)
		{
			if (m_Scenes.size())
				SetActiveScene(m_Scenes.begin()->first);
			else
				SetActiveScene(nullptr);
		}
	}

	bool SceneManager::IsLoaded(const std::string& scenePath)
	{
		return m_Scenes.find(scenePath) != m_Scenes.end();
	}

	void SceneManager::SaveSceneAs(const std::string& scenePath, const std::string& newScenePath)
	{
		if (!IsLoaded(scenePath))
		{
			CX_CORE_ERROR("Scene '{}' not loaded!", scenePath);
			return;
		}

		SceneSerializer serializer(GetScene(scenePath));
		serializer.SerializeSceneToFile("content/scenes/" + newScenePath + ".scene.json");
	}

	Scene* SceneManager::CreateEmptyScene(const std::string& scenePath)
	{
		auto scene = MakeShared<Scene>(m_GameInstance, scenePath);
		scene->m_GameInstance = m_GameInstance;
		m_Scenes[scenePath] = scene;
		return scene.get();
	}

}
