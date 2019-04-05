#pragma once
#include "Layer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class ImGuiLayer: public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer();
	virtual void OnAttachLayer(); 
	virtual void OnDetachLayer(); 
	GLFWwindow* imgui_window;
	

	virtual void OnUpdateLayer();
	virtual void OnEventLayer(Event& event);


};
