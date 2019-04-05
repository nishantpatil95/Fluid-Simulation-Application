#ifndef WINDOWS_H
#define WINDOWS_H

#include "pch.h"
#include "Event.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

struct WindowProps
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "Demo Window(1280x720)",
		unsigned int width = 1280,
		unsigned int height = 720)
		: Title(title), Width(width), Height(height)
	{
	}
};

// Interface representing a desktop system based Window
class  Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	virtual ~Window() {}

	virtual void OnUpdate() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	// Window attributes
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;
	virtual GLFWwindow* GetNativeWindow() const = 0;
	static Window* Create(const WindowProps& props = WindowProps());
};

class WindowsWindow : public Window
{
public:

	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
	GLFWwindow *GetNativeWindow() const override
	{
		return m_Window;
	}
private:
	virtual void Init(const WindowProps& props);
	
private:
	GLFWwindow * m_Window;
	virtual void Shutdown();
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		EventCallbackFn EventCallback;
	};

	WindowData m_Data;
};
#endif // !WINDOWS_H
