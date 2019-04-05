#ifndef FLUID_MECHANICS_APP_H
#define FLUID_MECHANICS_APP_H
#include "Common.h"
#include "Application.h"
#include "LayerStack.h"

#include "PixelGrid.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"



class FluidMechanicsApp : public Application
{
private:
	bool MouseButtonOnePressed = false;
	bool MouseButtonTwoPressed = false;
	static PixelGrid *s_obj_grid;
	float mousex;
	float mousey;

public:

	PixelGrid *grid;
	GLFWwindow* GUI_window;
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	FluidMechanicsApp(int argc, char* argv[]);
	~FluidMechanicsApp();
	//void setbackground(float r, float g, float b, float a );
	void OnSetupApplication() override;
	void OnUpdateApplication() override;
	bool OnMouseButtonEvent(MouseButtonEvent & e) override;
	bool OnMouseMovedEvent(MouseMovedEvent & e) override;
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) override;
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) override;
	bool OnWindowResizeEvent(WindowResizeEvent& e) override;
	void Reset();
	void static GenerateRandomPattern();
};


#endif // !FLUID_MECHANICS_APP_H

