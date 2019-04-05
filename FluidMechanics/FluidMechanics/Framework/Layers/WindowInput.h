#pragma once
#ifndef WINDOWINPUT_H
#define WINDOWINPUT_H
#include "Application.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"
class WindowInput :public Input
{
public:
	bool KeyPressed(int keycode)
	{
		auto m_Window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(m_Window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool MouseButtonPressed(int button)
	{
		auto m_Window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(m_Window, button);
		return state == GLFW_PRESS;
	}
	void GetMousePosition(double &xpos, double &ypos)
	{
		auto m_Window = Application::Get().GetWindow().GetNativeWindow();
		glfwGetCursorPos(m_Window, &xpos, &ypos);
	}

};
#endif // !WINDOWINPUT_H

