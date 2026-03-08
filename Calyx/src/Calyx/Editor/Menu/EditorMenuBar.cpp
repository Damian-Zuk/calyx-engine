#include "cxpch.h"
#ifdef CX_EDITOR
#include "Calyx/Editor/Menu/EditorMenuBar.h"
#include "Calyx/Editor/EditorLayer.h"
#include "Calyx/Editor/Tools/EditorCamera.h"
#include "Calyx/Editor/Panels/SceneViewportPanel.h"
#include "Calyx/Editor/Widget/ScriptEditWidget.h"
#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Scene/SceneManager.h"
#include "Calyx/Scripting/AppScript.h"
#include "Calyx/Scripting/ScriptFactory.h"
#include "Calyx/Network/NetworkManager.h"
#include "Calyx/Utils/Utils.h"

#include <imgui.h>

namespace Calyx {

	void EditorMenuBar::OnCreate()
	{
		m_SceneManager = EditorLayer::GetMainGameInstance()->GetSceneManager();
	}

	void EditorMenuBar::OnImGuiRender()
	{
		static bool openNewInstancePopupModal = false;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open scene...", "Ctrl+O"))
					OpenScene();

				ImGui::Separator();

				if (ImGui::MenuItem("New scene", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Save scene", "Ctrl+S"))
					SaveScene();

				if (ImGui::MenuItem("Save scene as...", "Ctrl+Shift+S"))
					SaveSceneAs();

				ImGui::Separator();

				if (ImGui::MenuItem("Exit"))
					Application::Get().Exit();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Project"))
			{
				if (ImGui::MenuItem("Project proporties"))
					m_OpenProjectProporties = true;

				if (ImGui::MenuItem("Save network config"))
					EditorLayer::GetMainGameInstance()->GetNetworkManager()->SaveConfig();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Editor"))
			{
				if (ImGui::MenuItem("Reset camera"))
				{
					auto viewport = EditorLayer::GetFocusedViewportPanel();
					viewport->m_Camera->SetPosition({0.0f, 0.0f, 0.0f});
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		HandleProjectProportiesPopup();
	}

	static std::string GetSceneFilename(const std::string& filepath)
	{
		std::size_t pos = filepath.find("scenes");
		if (pos != std::string::npos) {
			std::string filename = filepath.substr(pos + 7);
			std::size_t posExt = filepath.find(".scene.json");
			if (posExt != std::string::npos)
				return filename.substr(0, filename.size() - 11);
			return filename;
		}
		return std::string();
	}

	void EditorMenuBar::NewScene()
	{
		Scene* scene = m_SceneManager->CreateEmptyScene();
		m_SceneManager->m_ActiveScene = scene;
		EditorLayer::SetActiveScene(scene);
	}

	void EditorMenuBar::OpenScene()
	{
		std::string sceneFile = GetSceneFilename(FileDialogs::OpenFile("scene"));
		if (sceneFile.size())
		{
			m_SceneManager->Load(sceneFile);
			m_SceneManager->SetActiveScene(sceneFile);
		}
	}

	void EditorMenuBar::SaveScene()
	{
		Scene* scene = m_SceneManager->GetActiveScene();
		if (!scene)
			return;

		if (scene->m_Filepath != "<Unsaved scene>")
		{
			const std::string filepath = scene->m_Filepath;
			m_SceneManager->SaveSceneAs(filepath, filepath);
		}
		else
			SaveSceneAs();
	}

	void EditorMenuBar::SaveSceneAs()
	{
		Scene* scene = m_SceneManager->GetActiveScene();
		if (!scene)
			return;

		std::string filepath = GetSceneFilename(FileDialogs::SaveFile(".scene.json"));
		if (filepath.size())
		{
			m_SceneManager->SaveSceneAs(scene->m_Filepath, filepath);
			if (scene->m_Filepath == "<Unsaved scene>")
			{
				m_SceneManager->Unload("<Unsaved scene>");
			}
			m_SceneManager->Load(filepath);
			m_SceneManager->SetActiveScene(filepath);
		}
	}

	void EditorMenuBar::HandleProjectProportiesPopup()
	{
		if (m_OpenProjectProporties)
			ImGui::OpenPopup("Project Proporties");

		if (ImGui::BeginPopupModal("Project Proporties", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ProjectConfig& project = EditorLayer::GetMainGameInstance()->m_ProjectConfig;

			char buffer[256];
			strcpy_s(buffer, project.StartScene.c_str());

			ImGui::Dummy({ 0, 5 });
			ImGui::PushItemWidth(150.0f);
			if (ImGui::InputText("Startup scene", buffer, 256))
			{
				project.StartScene = buffer;
			}
			ImGui::PopItemWidth();

			ImGui::Dummy({ 0, 5 });
			ImGui::Text("App Script");
			ImGui::Dummy({ 0.0f, 5.0f });
			GameInstance* gameInstance = Application::GetGameInstance();
			const std::string& selectedGameScript = gameInstance->m_AppScript->GetScriptClassName();
			ImGui::PushItemWidth(210.0f);
			if (ImGui::BeginCombo("AppScript Class", selectedGameScript.c_str()))
			{
				for (auto& [className, instanciateFunc] : ScriptFactory::Get().m_AppFuncRegistry)
				{
					bool selected = selectedGameScript == className;
					if (ImGui::Selectable(className.c_str(), selected))
					{
						gameInstance->SetAppScript(className);
					}
				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Dummy({ 0.0f, 5.0f });

			ScriptEditWidget::DrawFieldEdit(gameInstance->m_AppScript);

			ImGui::Dummy({ 0, 10 });

			if (ImGui::Button("Save", {150, 0}))
			{
				project.WriteConfig();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", { 150, 0 })) { ImGui::CloseCurrentPopup(); }

			ImGui::EndPopup();
			m_OpenProjectProporties = false;
		}
	}
}

#endif // CX_EDITOR
