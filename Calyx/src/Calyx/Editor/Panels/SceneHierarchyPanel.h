#pragma once
#ifdef CX_EDITOR
#include "Calyx/Editor/Panels/EditorPanel.h"

namespace Calyx {

	class SceneHierarchyPanel : public EditorPanel 
	{
	public:
		virtual void OnImGuiRender() override;
	
	private:
		void DrawEntityTreeNode(Entity entity);

	private:
		Entity m_TreeNodeHovered;

		friend class SceneViewportPanel;
	};

}
#endif // CX_EDITOR
