#include "cxpch.h"
#ifdef CX_EDITOR
#include "Calyx/Editor/Panels/SceneViewportPanel.h"
#include "Calyx/Editor/Tools/EditorCamera.h"
#include "Calyx/Editor/EditorLayer.h"

#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Core/Input.h"
#include "Calyx/Events/MouseEvents.h"
#include "Calyx/Events/WindowEvents.h"

#include <imgui.h>

namespace Calyx {

	EditorCamera::EditorCamera(SceneViewportPanel* viewportPanel)
		: m_ViewportPanel(viewportPanel)
	{
	}

	void EditorCamera::OnUpdate(float ts)
	{
		Scene* scene = EditorLayer::GetActiveScene();
		if (!scene)
			return;

		if (m_IsDragging)
		{
			const glm::vec2& cursor = scene->GetCursorWorldPosition();
			glm::vec2 offset = m_CameraDragOffset - cursor;
			m_Position.x += offset.x;
			m_Position.y += offset.y;
			ImGui::SetMouseCursor(2);
		}

		if (scene->m_State == SceneState::Stop || m_UseInRuntime)
		{
			float zoomLevel = m_Camera.GetZoomLevel();
			float zoomTargetDiff = glm::abs(m_ZoomLevelTarget - zoomLevel);
			float zoomOffset = glm::max(glm::round(zoomTargetDiff * ts * 10000.0f) / 1000.0f, 0.001f);

			if (m_ZoomLevelTarget > zoomLevel)
			{
				m_Camera.SetZoomLevel(glm::min(zoomLevel + zoomOffset, m_ZoomLevelTarget));
			}
			else if (m_ZoomLevelTarget < zoomLevel)
			{
				m_Camera.SetZoomLevel(glm::max(zoomLevel - zoomOffset, m_ZoomLevelTarget));
			}
		}
	}	

	void EditorCamera::OnEvent(Event& e)
	{
		Scene* scene = m_ViewportPanel->m_GameInstance->GetActiveScene();

		if (!scene || (!m_ViewportPanel->m_IsViewportHovered && !m_IsDragging))
			return;

		auto focusedGameInstasnce = EditorLayer::GetFocusedGameInstance();
		if (m_ViewportPanel->m_GameInstance != focusedGameInstasnce)
			return;

		if (scene->m_State == SceneState::Stop || m_UseInRuntime)
		{
			EventDispatcher dispatcher(e);
			
			dispatcher.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent& e)
			{
				const glm::vec2& cursor = scene->GetCursorWorldPosition();
					
				if (e.GetMouseButton() == Mouse::Button1 && !m_IsDragging
					&& (scene->m_State == SceneState::Stop || m_UseInRuntime))
				{
					m_CameraDragOffset = cursor;
					m_IsDragging = true;
				}
				return false;
			});

			dispatcher.Dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent& e)
			{
				if (e.GetMouseButton() == Mouse::Button1)
					m_IsDragging = false;

				ImGui::SetMouseCursor(0);
				return false;
			});

			dispatcher.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& event) -> bool 
			{
				float zoomOffset = m_CameraZoomSpeed * -event.GetYOffset();
				m_ZoomLevelTarget += round(zoomOffset * round(m_ZoomLevelTarget * 10.0f) * 1000.0f) / 10000.0f;
				m_ZoomLevelTarget = glm::clamp(m_ZoomLevelTarget, 0.1f, 30.0f);
				return false;
			});
		}
	}

	void EditorCamera::SetViewportSize(const glm::vec2& viewportSize)
	{
		m_Camera.SetViewportSize(viewportSize);
	}

	void EditorCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

}
#endif // CX_EDITOR
