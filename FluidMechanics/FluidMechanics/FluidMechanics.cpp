

#include "pch.h"
#include "Application.h"
#include "FluidMechanicsApp.h"


#include <Windows.h>
#include "Glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main(int argc, char* argv[]) {
	
	Parameters::GuiHeight = Parameters::Height;
	Parameters::GuiWidth = Parameters::Width;
	Parameters::GuiPixelSize = Parameters::PixelSize;
	
	while (Parameters::RestartApp)
	{
		thread *th;
		Parameters::appRunning = false;
		th = new thread(FluidMechanicsApp::GenerateRandomPattern);
		FluidMechanicsApp *AppObj;
		AppObj = new FluidMechanicsApp(argc, argv);
		AppObj->Run();
		delete AppObj;
		th->detach();

		Parameters::Height = Parameters::GuiHeight;
		Parameters::Width = Parameters::GuiWidth;
		Parameters::PixelSize = Parameters::GuiPixelSize;
	}
	

	  // Setup window
	
	/*FluidMechanicsApp *AppObj;
	int ch;
	while (1)
	{
		cout << "===========================" << endl;
		cout << "=====ENTER A CHOICE========" << endl;
		cout << "===========================" << endl;
		cout << "1 . Start App " << endl;
		cout << "2 . Change Initial Parameters (Resolution,PixelSize,BackGround Color)" << endl;
		cout << "3 . Generate Random pattern" << endl;
		cout << "9 . Exit" << endl;

		cin >> ch;
		if (ch == 9)
			break;
		thread *th;
		switch (ch)
		{
		case 1:  AppObj= new FluidMechanicsApp(argc, argv);
			Parameters::appRunning = true;
			th=new thread(Parameters::changeRunningParameters);
			 
			AppObj->Run();
			delete AppObj;
			Parameters::appRunning = false;
			th->join();
			//th->detach();
			break;
		case 2:Parameters::changeInitialParameters();
			break;
		case 3:AppObj = new FluidMechanicsApp(argc, argv);
			Parameters::appRunning = true;
			th = new thread(FluidMechanicsApp::GenerateRandomPattern);
			AppObj->Run();
			delete AppObj;
			Parameters::appRunning = false;
			th->join();
			//th->detach();
			break;
		case 9:exit(0);
			
		default:cout << "Invalid Choice" << endl;
			continue;
		}
	};

	*/

	LOG("%s", "Running Stoped");

	return 0;
}
