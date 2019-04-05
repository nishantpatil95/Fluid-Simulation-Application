#include "pch.h"
#include "ImGuiLayer.h"
#include "Application.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"


ImGuiLayer::ImGuiLayer():Layer("ImGuiLayer")
{

};
ImGuiLayer::~ImGuiLayer()
{

};

 void ImGuiLayer::OnAttachLayer() {
	


 }
 void ImGuiLayer::OnDetachLayer() {

 }


void ImGuiLayer::OnUpdateLayer() {
	
}
void ImGuiLayer::OnEventLayer(Event& event) {
	//LOG("Layer::OnEventLayer called")
}