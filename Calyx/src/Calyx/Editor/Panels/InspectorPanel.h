#pragma once
#ifdef CX_EDITOR
#include "Calyx/Editor/Panels/EditorPanel.h"

namespace Calyx {

	class InspectorPanel : public EditorPanel
	{
	public:
		virtual void OnImGuiRender() override;

	private:
		void DrawSceneProporties();

		template<typename T>
		void DrawComponentUI(const std::string& name, const std::function<void(T&)>& drawContentFunction);

		friend class EditorLayer;
		friend class SceneViewportPanel;
		friend class SettingsPanel;
	};

}

#endif // CX_EDITOR
