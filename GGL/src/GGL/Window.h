#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <stdint.h>

namespace GGL
{
	struct WindowOptions
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool CoreProfile;

		WindowOptions(const std::string& title = "Sandbox", uint32_t width = 640, uint32_t height = 480, bool coreProfile = false)
			: Title(title), Width(width), Height(height), CoreProfile(coreProfile)
		{
		}
	};

	class Window
	{
	public:
		Window(const WindowOptions& opts = WindowOptions());
		~Window();
		void Update();
		void EnableVSync() const { glfwSwapInterval(1); }

		inline bool IsOpen() const { return !glfwWindowShouldClose(m_Window); } 
		inline void Exit() const { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }
		inline void Clear() const { glClear(GL_COLOR_BUFFER_BIT); }
		inline GLFWwindow* GetNativeWindow() const { return m_Window; }
	private:
		void Boot(const WindowOptions&);
		void Shutdown();
	private:
		GLFWwindow* m_Window;
	};
}