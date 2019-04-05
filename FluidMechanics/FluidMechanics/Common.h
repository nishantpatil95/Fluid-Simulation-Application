#pragma once

#ifndef CORE_H
#define CORE_H

//#include "pch.h"
#define SUCCESS 0
#define FAILURE -1

#define WINDOW_NAME "Fluid Mechanics "

class Parameters
{
public:
	static bool appRunning;
	static int Height;
	static int Width;
	static int PixelSize;

	static int GuiHeight;
	static int GuiWidth;
	static int GuiPixelSize;

	static float Diffusion;
	static float Viscosity;
	static float TimeDifference;
	static float DensityAmount;


	static float BackGroundColorR;
	static float BackGroundColorG;
	static float BackGroundColorB;
	static float BackGroundColorA;

	static float PrimaryColorR;
	static float PrimaryColorB;
	static float PrimaryColorG;
	static float PrimaryColorA;

	static float SecondaryColorR;
	static float SecondaryColorB;
	static float SecondaryColorG;
	static float SecondaryColorA;

	static bool RestartApp;
	

	static void ChangeIntParameter(const char *name, int *ptr, float r1, float r2);
	static void ChangeFloatParameter(const char *name, float *ptr, float r1, float r2);

		static void changeInitialParameters();
		static void changeRunningParameters();

		
};



#define BIT(x) (1 << x)

#define LOG(x,...) printf("%s %s %d ",get_Name(__FILE__),__func__,__LINE__);printf(x,__VA_ARGS__);printf("%s","\n"); 
//#define LOG(x,...) 
//#define LOG(x,...) fprintf(fp,"%s %s %d ",get_Name(__FILE__),__func__,__LINE__);fprintf(fp,x,__VA_ARGS__);fprintf(fp,"%s","\n"); 
//static FILE *fp;

const char * get_Name(const char * file_path);
float interpolate(float x0, float x1, float y1, float x2, float y2);
float constaint(float n, float  n1, float  n2);

float random_range(float n1, float n2);
#endif // !CORE_H




