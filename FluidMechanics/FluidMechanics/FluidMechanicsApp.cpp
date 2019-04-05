#pragma once
#include "pch.h"
#include "FluidMechanicsApp.h"
#include "WindowInput.h"
#include "PixelGrid.h"
#include "ImGuiLayer.h"


FluidMechanicsApp::FluidMechanicsApp(int argc, char* argv[]) :Application(argc, argv)
{
	//LOG("Welcome To Fluid App");
	//PushLayer(new ImGuiLayer());

	
	if (!glfwInit())
		LOG("Failed in glfwInit")

	// Decide GL+GLSL versions


	// Create window with graphics context
	GUI_window = glfwCreateWindow(400, 600, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	if (GUI_window == NULL)
		LOG("Failed in GUI_window")


	//glfwMakeContextCurrent(GUI_window);


	//glfwSwapInterval(1); // Enable vsync
		IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(GUI_window, true);
	

	// Setup style
	ImGui::StyleColorsDark();


}

FluidMechanicsApp::~FluidMechanicsApp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(GUI_window);
	//glfwTerminate();
	delete grid;
}
// This will identify our vertex buffer
bool FluidMechanicsApp::OnWindowResizeEvent(WindowResizeEvent& e)
{

	//LOG("Window Resized to %ud X %ud", e.GetWidth(), e.GetHeight())
	grid->Resize(e.GetWidth(), e.GetHeight());
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	return true;
}
bool FluidMechanicsApp::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	if (e.GetMouseButton() == 1)
		MouseButtonOnePressed = true;
	else
		MouseButtonTwoPressed = true;
	return true;
}
bool FluidMechanicsApp::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	if (e.GetMouseButton() == 1)
		MouseButtonOnePressed = false;
	else
		MouseButtonTwoPressed = false;
	return true;
}
bool FluidMechanicsApp::OnMouseMovedEvent(MouseMovedEvent & e)
{
	//LOG("Moved X::%0.2f Y::%0.2f",interpolate(e.GetX(),0,1279,-1,1), interpolate(e.GetY(), 0, 719, 1, -1))
	//LOG("Moved X::%0.2f Y::%0.2f", e.GetX(), e.GetY())
	float dx = -floor(interpolate(mousex - e.GetX(), 500, -500, 100.0f, -100.0f));
	float dy = -floor(interpolate(mousey - e.GetY(), 500, -500, 100.0f, -100.0f));

	//float dx = mousex - e.GetX();
	//float dy = mousey - e.GetY();
	mousex = e.GetX();
	mousey = e.GetY();
	//LOG("%0.9f %0.9f ",dx,dy)
	//dx = 1000000.0f;


	if (MouseButtonTwoPressed)
	{

		grid->AddMovementPrimary(e.GetX(), e.GetY(), dx, dy);
	//	LOG("Moved X::%0.2f Y::%0.2f", e.GetX(), e.GetY())
			//grid->Refresh();
	}
	if (MouseButtonOnePressed)
	{
		grid->AddMovementSecondary(e.GetX(), e.GetY(), dx, dy);
	//	LOG("Moved X::%0.2f Y::%0.2f", e.GetX(), e.GetY())
			//grid->Refresh();
	}
	return true;
}
bool FluidMechanicsApp::OnMouseButtonEvent(MouseButtonEvent & e)
{
	return true;
}
GLuint Shader::program = 0;
void FluidMechanicsApp::OnSetupApplication()
{
	grid = new PixelGrid(Parameters::PixelSize);

	s_obj_grid = grid;


	// glViewport(0,0,1280, 720);
}

void FluidMechanicsApp::Reset()
{
	grid->InitializeData(Parameters::Width, Parameters::Height, Parameters::BackGroundColorR, Parameters::BackGroundColorG, Parameters::BackGroundColorB, Parameters::BackGroundColorA);
}
void FluidMechanicsApp::OnUpdateApplication()
{
	if (!glfwWindowShouldClose(GUI_window))
	{
		glfwMakeContextCurrent(GUI_window);
		glfwSwapBuffers(GUI_window);
		//==========================================================================================

			// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
		//	ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

		static float f = 0.0f;
		//static int counter = 0;

		ImGui::Begin("Parameters");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		 // Edit 3 floats representing a color
		/******************** Control  parameters *******************/


		ImGui::SliderFloat("Time", &Parameters::TimeDifference, -10, 10);
		ImGui::SliderFloat("Viscosity", &Parameters::Viscosity, 0, 5);
		ImGui::Checkbox("Auto Click", &Parameters::appRunning);


		ImGui::SliderFloat("Diffusion", &f, 0, 5);
		Parameters::Diffusion = interpolate(f, 0, 5, 0, 0.00001);
		ImGui::SliderFloat("Density Amount", &Parameters::DensityAmount, -100, 100);


		ImGui::ColorEdit3("Back Ground Color", (float*)&Parameters::BackGroundColorR);
		ImGui::ColorEdit3("Primary Color", (float*)&Parameters::PrimaryColorR);
		ImGui::ColorEdit3("Secondary Color", (float*)&Parameters::SecondaryColorR);

		if (ImGui::Button("Reset"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			Reset();
		ImGui::SliderInt("Window Height ", &Parameters::GuiHeight, 0, 1000);
		ImGui::SliderInt("Window Width", &Parameters::GuiWidth, 0, 1000);
		ImGui::SliderInt("Pixel Size", &Parameters::GuiPixelSize, 0, 100);
		if (ImGui::Button("Restart Application"))
		{
			//Parameters::RestartApp = false;
			m_Running = false;
		}


		if (ImGui::Button("Close Application"))
		{
			Parameters::RestartApp = false;
			m_Running = false;
		}
		// Buttons return true when clicked (most widgets return true when edited/activated)
	//		Restart();


		/******************** Control  parameters *******************/
	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	ImGui::SameLine();
	//	ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();



		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(GUI_window);
		glfwGetFramebufferSize(GUI_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
	else
	{
		Parameters::RestartApp = false;
		m_Running = false;
	}
	
	//==========================================================================================




	glfwMakeContextCurrent(Application::Get().GetWindow().GetNativeWindow());
	//glfwSwapBuffers(Application::Get().GetWindow().GetNativeWindow());
	grid->draw();

}
void FluidMechanicsApp::GenerateRandomPattern()
{
	Parameters::BackGroundColorR = random_range(0, 1);
	Parameters::BackGroundColorG = random_range(0, 1);
	Parameters::BackGroundColorB = random_range(0, 1);
	Parameters::BackGroundColorA = random_range(0, 1);
	cout << "BackGround R  "<< Parameters::BackGroundColorR <<endl;
	cout << "BackGround G  " << Parameters::BackGroundColorG <<endl;
	cout << "BackGround B  " << Parameters::BackGroundColorB <<endl;
	cout << "BackGround A  " << Parameters::BackGroundColorA <<endl;

	Parameters::PrimaryColorR = random_range(-1, 1);
	Parameters::PrimaryColorG = random_range(-1, 1);
	Parameters::PrimaryColorB = random_range(-1, 1);
	Parameters::PrimaryColorA = random_range(-1, 1);
	cout << "Primary R  " << Parameters::PrimaryColorR << endl;
	cout << "Primary G  " << Parameters::PrimaryColorG << endl;
	cout << "Primary B  " << Parameters::PrimaryColorB << endl;
	cout << "Primary A  " << Parameters::PrimaryColorA << endl;

	Parameters::SecondaryColorR = random_range(-1, 1);
	Parameters::SecondaryColorG = random_range(-1, 1);
	Parameters::SecondaryColorB = random_range(-1, 1);
	Parameters::SecondaryColorA = random_range(-1, 1);
	cout << "Secondary R  " << Parameters::SecondaryColorR << endl;
	cout << "Secondary G  " << Parameters::SecondaryColorG << endl;
	cout << "Secondary B  " << Parameters::SecondaryColorB << endl;
	cout << "Secondary A  " << Parameters::SecondaryColorA << endl;

	
	while (1)
	{
		if(Parameters::appRunning)
		if (s_obj_grid)
		{
		//	cout << "Ranfodm" << endl;
			//Parameters::Diffusion= random_range(0,1);
			//Parameters::Viscosity = random_range(0, 0.00005);
			//Parameters::TimeDifference = random_range(-10, 10);
		//	Parameters::DensityAmount = random_range(-100, 100);
			//cout << "App Running  " << random_range(-100, 100) << endl;
			s_obj_grid->AddMovementPrimary(random_range(0, Parameters::Width), random_range(0, Parameters::Height), random_range(-100, 100), random_range(-100, 100));
			s_obj_grid->AddMovementSecondary(random_range(0, Parameters::Width), random_range(0, Parameters::Height), random_range(-100, 100), random_range(-100, 100));
		}
		Sleep(1000);
		
	}
}
PixelGrid *FluidMechanicsApp::s_obj_grid = nullptr;
