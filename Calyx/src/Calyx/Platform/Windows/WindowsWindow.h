#pragma once

#include "Calyx/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Calyx {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& spec);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;
		virtual void* GetNativeWindow() const { return m_Window; }

		virtual void SetVSync(bool enabled) override;
		virtual void SetFullscreen(bool fullscreen = true) override;

	private:
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		// For disabling fullscreen and restoring previous width and height
		uint32_t m_PreviousWidth;
		uint32_t m_PreviousHeight;
	};

}
