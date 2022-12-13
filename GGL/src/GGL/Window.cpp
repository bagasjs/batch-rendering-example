#include "Window.h"
#include <GLFW/glfw3.h>

namespace GGL
{
	Window::Window(const WindowOptions& opts)
	{
		Boot(opts);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Boot(const WindowOptions& opts)
	{		
		if(!glfwInit()) exit(-1);
		m_Window = glfwCreateWindow(opts.Width, opts.Height, opts.Title.c_str(), NULL, NULL);
		if(!m_Window)
		{
			Shutdown();
		}

		if(opts.CoreProfile == true)
		{
			glfwWindowHint(GLFW_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		glfwMakeContextCurrent(m_Window);
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}