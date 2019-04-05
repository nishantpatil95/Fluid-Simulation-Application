#ifndef APPLICATION_H
#define APPLICATION_H
#include "pch.h"
#include "Input.h"
#include "LayerStack.h"
#include "Event.h"
#include "Window.h"

#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"

class Application
{
private:
	LayerStack m_LayerStack;
	void OnEvent(Event& e);

	bool OnWindowClose(WindowCloseEvent& e);

	
	
protected:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	float bg_r, bg_g, bg_b, bg_a;

	void virtual PushLayer(Layer* layer);
	void virtual PushOverlay(Layer* layer);
	Application(int argc, char* argv[]);

	void virtual OnSetupApplication();
	void virtual OnUpdateApplication();
	bool virtual OnMouseButtonEvent(MouseButtonEvent& e);
	bool virtual OnMouseMovedEvent(MouseMovedEvent & e);
	bool virtual OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool virtual OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool virtual OnWindowResizeEvent(WindowResizeEvent& e);

public:
	double MouseX;
	double MouseY;
	bool MouseButtonClicked = false;
	Application();
	static Application *s_Instance;
	inline static Application& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }
	bool setBackGround(float r, float g, float b, float a);
	bool StopRunning();
	virtual ~Application();
	void Run();
	static Application * CreateApplication(int argc, char* argv[]);
};
#endif // !APPLICATION_H
