#include "cxpch.h"
#ifdef CX_EDITOR
#include "Calyx/Editor/Panels/EditorPanel.h"
#include "Calyx/Editor/EditorLayer.h"

namespace Calyx {

	Entity EditorPanel::GetSelectedEntity(bool targetMainInstance)
	{
		return EditorLayer::GetSelectedEntity(targetMainInstance);
	}

	Scene* EditorPanel::GetActiveScene(bool targetMainInstance)
	{
		return EditorLayer::GetActiveScene(targetMainInstance);
	}

}
#endif // CX_EDITOR
