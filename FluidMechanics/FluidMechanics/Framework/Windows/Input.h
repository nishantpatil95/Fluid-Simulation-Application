#ifndef INPUT_H
#define INPUT_H
#include "pch.h"
class Input
{
public:
	static bool IsKeyPressed(int keycode)
	{
		return s_Instance->KeyPressed(keycode);
	}
	static bool IsMouseButtonPressed(int button)
	{
		return s_Instance->MouseButtonPressed(button);
	}
	static void  GetMouseCurPosition(double &xpos, double &ypos)
	{
		s_Instance->GetMousePosition(xpos, ypos);
	}
	virtual bool KeyPressed(int keycode) = 0;
	virtual bool MouseButtonPressed(int button) = 0;
	virtual void  GetMousePosition(double &xpos, double &ypos) = 0;

	static Input * s_Instance;
};

#endif // !_INPUT_H

