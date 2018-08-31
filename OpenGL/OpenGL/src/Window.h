#pragma once



#include <string>

struct GLFWwindow;

class Window
{
public:
	Window(int& width, int& height, float& scale, const std::string& title, const std::string& icon_path = "");
	~Window();

	inline GLFWwindow* GetWindow() const { return m_window; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline float GetScale() const { return m_scale; }
	inline std::string GetTitle() const { return m_title; }
	void SetTitle(std::string& title);
private:
	GLFWwindow* m_window;
	int m_width, m_height, m_mod_width, m_mod_height;
	float m_scale;
	std::string m_title;
	std::string m_icon_path;

	static bool m_init;
};

