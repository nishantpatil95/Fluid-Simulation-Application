#include "pch.h"
#include "Common.h"
int Parameters::Height = 1000;
int Parameters::Width = 1200;
int Parameters::PixelSize = 20;

int Parameters::GuiHeight = 0;
int Parameters::GuiWidth = 0;
int Parameters::GuiPixelSize = 0;

bool Parameters::RestartApp = true;

float Parameters::BackGroundColorR = 0.0f;
float Parameters::BackGroundColorG = 0.0f;
float Parameters::BackGroundColorB = 0.0f;
float Parameters::BackGroundColorA = 1.0f;

float Parameters::PrimaryColorR = 0.2f;
float Parameters::PrimaryColorG = 0.5f;
float Parameters::PrimaryColorB = 0.1f;
float Parameters::PrimaryColorA = 1.0f;

float Parameters::SecondaryColorR = 0.5f;
float Parameters::SecondaryColorG = 0.1f;
float Parameters::SecondaryColorB = 0.9f;
float Parameters::SecondaryColorA = 1.0f;

float Parameters::TimeDifference = 1.0f;
float Parameters::Viscosity = 0.000f;
float Parameters::Diffusion = 0.000f;

float Parameters::DensityAmount = 100.0f;

bool Parameters::appRunning = false;
const char * get_Name(const char * file_path)
{
	const char *name;
	name = &file_path[strlen(file_path) - 1];
	while (*name != '\\')
	{
		name--;
	}
	return name + 1;
}


float random_range(float n1, float n2)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<double> distribution(n1, n2);

	return distribution(generator);
}


float interpolate(float x0, float x1, float x2, float y1, float y2)
{
	return  ((y2 - y1) / (x2 - x1))*(x0 - x1) + y1;
}


float constaint(float n, float  n1, float  n2)
{
	//LOG("n1::%0.9f", n1);
	//LOG("n1::%0.9f", n2);
	//return n;
	if (n1 > n2)
	{
		int t = n1;
		n1 = n2;
		n2 = t;
	}

	if (n <= n2 && n >= n1)
		return n;
	else if (n > n2)
		return n2;
	else
		return n1;

}


void Parameters::ChangeIntParameter(const char *name, int *ptr, float r1, float r2)
{
	cout << "Enter value for " << name << " between " << r1 << " and  " << r2 << endl;
	int val=0;
	cin >> val;
	*ptr = val;
	cout << name << " is set to " << *ptr << endl;
}


void Parameters::ChangeFloatParameter(const char *name, float *ptr, float r1, float r2)
{
	cout << "Enter value for " << name << " between " << r1 << " and  " << r2 << endl;
	float val = 0;
	cin >> val;
	*ptr = val;
	cout << name << " is set to " << *ptr << endl;
}


void Parameters::changeRunningParameters()
{
	while (Parameters::appRunning)
	{
		cout << "==========================================" << endl;
		cout << "1. Primary Color :: R::" << Parameters::PrimaryColorR << " G::" << Parameters::PrimaryColorG << " B::" << Parameters::PrimaryColorB << " A::" << Parameters::PrimaryColorA << endl;
		cout << "2. Secondary Color :: R::" << Parameters::SecondaryColorR << " G::" << Parameters::SecondaryColorG << " B::" << Parameters::SecondaryColorB << " A::" << Parameters::SecondaryColorA << endl;
		cout << "3. Time Difference :: " << Parameters::TimeDifference << endl;
		cout << "4. Viscosity :: " << Parameters::Viscosity << endl;
		cout << "5. Diffusion :: " << Parameters::Diffusion << endl;
		cout << "6. DensityAmount :: " << Parameters::DensityAmount << endl;
		cout << "9. Exit" << endl;
		int ch;
		cin >> ch;
		switch (ch)
		{
			case 1:
				ChangeFloatParameter("Primary Color R",&PrimaryColorR, 0 ,1.0f );
				ChangeFloatParameter("Primary Color G",&PrimaryColorG, 0 ,1.0f );
				ChangeFloatParameter("Primary Color B",&PrimaryColorB, 0 ,1.0f );
				ChangeFloatParameter("Primary Color A",&PrimaryColorA, 0 ,1.0f );
				break;
			case 2:
				ChangeFloatParameter("Secondary Color R", &SecondaryColorR, 0, 1.0f);
				ChangeFloatParameter("Secondary Color G", &SecondaryColorG, 0, 1.0f);
				ChangeFloatParameter("Secondary Color B", &SecondaryColorB, 0, 1.0f);
				ChangeFloatParameter("Secondary Color A", &SecondaryColorA, 0, 1.0f);
				break;
			case 3:ChangeFloatParameter("Time Difference", &TimeDifference, 0.0f, 1.0f);
			break;
			case 4:ChangeFloatParameter("Viscosity", &Viscosity, 0.0f, 1.0f);
			break;
			case 5:ChangeFloatParameter("Diffusion", &Diffusion, 0.0f, 1.0f);
			break;
			case 6:ChangeFloatParameter("DensityAmount", &DensityAmount, 0.0f, 100.0f);
			break;
			default:cout << "Invalid Option" << endl;
			break;
		}
	}
}


void Parameters::changeInitialParameters()
{
	cout << "Current Values" << endl;
	cout << "1.Height::" << Height << endl;
	cout << "2.Width::" << Width << endl;
	cout << "3.PixelSize::" << PixelSize << endl;
	cout << "4.BackGround Color :: R::" << Parameters::BackGroundColorR << " G::" << Parameters::BackGroundColorG << " B::" << Parameters::BackGroundColorB << " A::" << Parameters::BackGroundColorA << endl;
	cout << "Enter Choice to change value " << PixelSize << endl;

	int ch;
	cin >> ch;
	switch (ch)
	{
		case 1:ChangeIntParameter("Height", &Height, 0, 1080);break;
		case 2:ChangeIntParameter("Width", &Width, 0, 1920);break;
		case 3:ChangeIntParameter("PixelSize", &PixelSize, 10,100 );break;
		case 4:
			ChangeFloatParameter("BackGround Color R", &BackGroundColorR, 0.0f, 1.0f);
			ChangeFloatParameter("BackGround Color G", &BackGroundColorG, 0.0f, 1.0f);
			ChangeFloatParameter("BackGround Color B", &BackGroundColorB, 0.0f, 1.0f);
			ChangeFloatParameter("BackGround Color A", &BackGroundColorA, 0.0f, 1.0f);
			break;
		default:cout << "Invalid Choice" << endl;
	}
}
