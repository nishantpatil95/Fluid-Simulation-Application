#include "pch.h"
#include "Application.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"
Application *Application::s_Instance = nullptr;

Application::Application()
{
	cout << "Application is Created" << endl;
}
Application::Application(int argc, char* argv[])
{
	LOG("%s", "Application is Created");
	s_Instance = this;
	//m_Window = std::unique_ptr<Window>(Window::Create());
	WindowProps WindowPropsObj(WINDOW_NAME, Parameters::Width, Parameters::Height);
	m_Window = std::unique_ptr<Window>(Window::Create(WindowPropsObj));
	m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

}
void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttachLayer();
}
void Application::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttachLayer();
}

void Application::OnEvent(Event& e)
{
	//LOG("%s","Application::OnEvent");
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	dispatcher.Dispatch<MouseButtonEvent>(BIND_EVENT_FN(OnMouseButtonEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMovedEvent));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResizeEvent));
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEventLayer(e);
		if (e.Handled)
			break;
	}

}
bool Application::OnWindowResizeEvent(WindowResizeEvent& e)
{
	return true;
}
bool Application::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{

	return true;
}
bool Application::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{

	return true;
}
bool Application::OnWindowClose(WindowCloseEvent& e)
{
	LOG("On Window Closed called")
		Parameters::RestartApp = false;
		m_Running = false;
	return true;
}
bool Application::StopRunning()
{
	m_Running = false;

	return true;
}
bool Application::OnMouseButtonEvent(MouseButtonEvent & e)
{
	LOG("OnMouseButtonEventd called")

		return true;
}
bool Application::OnMouseMovedEvent(MouseMovedEvent & e)
{
	LOG("OnMouseMovedEventd called")

		return true;
}

Application::~Application()
{
	LOG("%s", "Application is Destroyed");
	//delete s_Instance;
}

void Application::Run()
{
	OnSetupApplication();
	while (m_Running)
	{
		//for (Layer* layer : m_LayerStack)
		//	layer->OnUpdateLayer();
		OnUpdateApplication();
		m_Window->OnUpdate();
	}
}

bool Application::setBackGround(float r, float g, float b, float a)
{
	bg_r = r;
	bg_g = g;
	bg_b = b;
	bg_a = a;
	return true;
}
Application *Application::CreateApplication(int argc, char* argv[])
{
	if (s_Instance == nullptr)
		s_Instance = new Application(argc, argv);
	return s_Instance;
}
void Application::OnSetupApplication()
{
	LOG("This is Called");
}
void Application::OnUpdateApplication()
{

}