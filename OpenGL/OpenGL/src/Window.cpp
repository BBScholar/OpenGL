#include "Window.h"

#include "ErrorManager.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "stb_image/stb_image.h"

bool Window::m_init = false;

Window::Window(int& width, int& height, float& scale, const std::string& title, const std::string& icon_path)
	: m_width(width), m_height(height), m_mod_width(0), m_mod_height(0), m_scale(scale), m_title(title), m_icon_path(icon_path)
{
	if (!m_init) {
		if (!glfwInit()) {
			std::cout << "GLFW not initialized" << std::endl;
			ASSERT(false);
		}
		m_init = true;
	}
	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	#ifdef DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
	#endif
	m_mod_width = (int)(m_width * m_scale);
	m_mod_height = (int)(m_height * m_scale);
	m_window = glfwCreateWindow(m_mod_width, m_mod_height, m_title.c_str(), NULL, NULL);

	if (!m_window) {
		glfwTerminate();
		std::cout << "Window could not be created!" << std::endl;
		ASSERT(false);
	}

	
	if (m_icon_path != "") {
		GLFWimage icons[1];
		icons[0].pixels = stbi_load(m_icon_path.c_str(), &icons[0].width, &icons[1].height, 0, 4);
		glfwSetWindowIcon(m_window, 1, icons);
		stbi_image_free(icons[0].pixels);
	}
	
	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::SetTitle(std::string& title)
{
	glfwSetWindowTitle(m_window, title.c_str());
	m_title = title;
}
