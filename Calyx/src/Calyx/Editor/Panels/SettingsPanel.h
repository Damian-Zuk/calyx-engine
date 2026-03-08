#pragma once
#ifdef CX_EDITOR
#include "Calyx/Editor/Panels/EditorPanel.h"

namespace Calyx {

	class SettingsPanel : public EditorPanel
	{
	public:
		virtual void OnImGuiRender() override;

		friend class Application;
		friend class EditorLayer;
	};

}

#endif // CX_EDITOR
