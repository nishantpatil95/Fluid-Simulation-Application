#pragma once
#ifndef PIXELGRID_H
#define PIXELGRID_H
#include "pch.h"
#include "Fluid2D.h"
#include "Glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"


class PixelGrid
{
private:
	int height;
	int width;
	int pixelsize;
	int viewHeight;
	int viewWidth;
	Shader shader;
	GLfloat *g_vertex_buffer_data;
	GLuint vertexbuffer;
	GLint mvp_location, vpos_location, vcol_location;
	vec4 m[4];
public:
	Fluid2D *ptrRCube;
	Fluid2D *ptrGCube;
	Fluid2D *ptrBCube;
	Fluid2D *ptrACube;
	
	PixelGrid(int pixelsize)
	{
		ptrRCube = new Fluid2D(Parameters::Width / Parameters::PixelSize, Parameters::Height / Parameters::PixelSize, &Parameters::Diffusion, &Parameters::Viscosity, &Parameters::TimeDifference);
		ptrGCube = new Fluid2D(Parameters::Width / Parameters::PixelSize, Parameters::Height / Parameters::PixelSize, &Parameters::Diffusion, &Parameters::Viscosity, &Parameters::TimeDifference);
		ptrBCube = new Fluid2D(Parameters::Width / Parameters::PixelSize, Parameters::Height / Parameters::PixelSize, &Parameters::Diffusion, &Parameters::Viscosity, &Parameters::TimeDifference);
		ptrACube = new Fluid2D(Parameters::Width / Parameters::PixelSize, Parameters::Height / Parameters::PixelSize, &Parameters::Diffusion, &Parameters::Viscosity, &Parameters::TimeDifference);
		
		//ptrCube =new Fluid2D(Parameters::Width / Parameters::PixelSize, Parameters::Height / Parameters::PixelSize, &Parameters::Diffusion, &Parameters::Viscosity, &Parameters::TimeDifference);
		InitializeData(Parameters::Width, Parameters::Height, Parameters::BackGroundColorR, Parameters::BackGroundColorG, Parameters::BackGroundColorB, Parameters::BackGroundColorA);
		InitializeBuffer();
	}
	~PixelGrid()
	{
		delete ptrRCube;
		delete ptrGCube;
		delete ptrBCube;
		delete ptrACube;
		//delete ptrCube;
		delete[]g_vertex_buffer_data;
	}
	void Resize(int Width, int Height)
	{
		viewHeight = Height;
		viewWidth = Width;
	}
	
	void InitializeData(int Width, int Height, float br, float bg, float bb, float ba)
	{
		height = Height / Parameters::PixelSize;
		width = Width / Parameters::PixelSize;
		viewHeight = Height;
		viewWidth = Width;
		LOG("height::%d  width::%d", height, width);
		if (g_vertex_buffer_data)
			delete[]g_vertex_buffer_data;
		g_vertex_buffer_data = new GLfloat[height*width * 28];

		// g_vertex_buffer_data = new GLfloat[20];
		LOG("buffer size::%d", height*width * 28);
		for (int i = 0;i < height;i++)
		{
			for (int j = 0;j < width;j++)
			{

				int x = j * Parameters::PixelSize;
				int y = i * Parameters::PixelSize;
				//x++;y++;
				//v1
				g_vertex_buffer_data[(i * width + j) * 28] = interpolate(x, 0, Width, -1, 1);
				g_vertex_buffer_data[(i * width + j) * 28 + 1] = interpolate(y, 0, Height, 1, -1);
				g_vertex_buffer_data[(i * width + j) * 28 + 2] = 0.0f;
				//c1
				g_vertex_buffer_data[(i * width + j) * 28 + 3] = br;
				g_vertex_buffer_data[(i * width + j) * 28 + 4] = bg;
				g_vertex_buffer_data[(i * width + j) * 28 + 5] = bb;
				g_vertex_buffer_data[(i * width + j) * 28 + 6] = ba;

				//v2
				g_vertex_buffer_data[(i * width + j) * 28 + 7] = interpolate(x + Parameters::PixelSize, 0, Width, -1, 1);
				g_vertex_buffer_data[(i * width + j) * 28 + 8] = interpolate(y, 0, Height, 1, -1);
				g_vertex_buffer_data[(i * width + j) * 28 + 9] = 0.0f;
				//c2
				g_vertex_buffer_data[(i * width + j) * 28 + 10] = br;
				g_vertex_buffer_data[(i * width + j) * 28 + 11] = bg;
				g_vertex_buffer_data[(i * width + j) * 28 + 12] = bb;
				g_vertex_buffer_data[(i * width + j) * 28 + 13] = ba;


				//v3
				g_vertex_buffer_data[(i * width + j) * 28 + 14] = interpolate(x + Parameters::PixelSize, 0, Width, -1, 1);
				g_vertex_buffer_data[(i * width + j) * 28 + 15] = interpolate(y + Parameters::PixelSize, 0, Height, 1, -1);
				g_vertex_buffer_data[(i * width + j) * 28 + 16] = 0.0f;
				//c3
				g_vertex_buffer_data[(i * width + j) * 28 + 17] = br;
				g_vertex_buffer_data[(i * width + j) * 28 + 18] = bg;
				g_vertex_buffer_data[(i * width + j) * 28 + 19] = bb;
				g_vertex_buffer_data[(i * width + j) * 28 + 20] = ba;


				//v4
				g_vertex_buffer_data[(i * width + j) * 28 + 21] = interpolate(x, 0, Width, -1, 1);
				g_vertex_buffer_data[(i * width + j) * 28 + 22] = interpolate(y + Parameters::PixelSize, 0, Height, 1, -1);
				g_vertex_buffer_data[(i * width + j) * 28 + 23] = 0.1f;
				//c4
				g_vertex_buffer_data[(i * width + j) * 28 + 24] = br;
				g_vertex_buffer_data[(i * width + j) * 28 + 25] = bg;
				g_vertex_buffer_data[(i * width + j) * 28 + 26] = bb;
				g_vertex_buffer_data[(i * width + j) * 28 + 27] = ba;


				/*	  //v1
					  g_vertex_buffer_data[(i * width + j) * 20] = interpolate(x, 0, WIDTH, -1, 1);
					  g_vertex_buffer_data[(i * width + j) * 20 + 1] = interpolate(y, 0, HEIGHT, 1, -1);

					  //c1
					  g_vertex_buffer_data[(i * width + j) * 20 + 2] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 3] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 4] = 0.5f;

					  //v2
					  g_vertex_buffer_data[(i * width + j) * 20 + 5] = interpolate(x + Parameters::PixelSize, 0, WIDTH, -1, 1);
					  g_vertex_buffer_data[(i * width + j) * 20 + 6] = interpolate(y, 0, HEIGHT, 1, -1)-1;

					  //c2
					  g_vertex_buffer_data[(i * width + j) * 20 + 7] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 8] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 9] = 0.5f;



					  //v3
					  g_vertex_buffer_data[(i * width + j) * 20 + 10] = interpolate(x + Parameters::PixelSize, 0, WIDTH, -1, 1);
					  g_vertex_buffer_data[(i * width + j) * 20 + 11] = interpolate(y + Parameters::PixelSize, 0, HEIGHT, 1, -1);

					  //c3
					  g_vertex_buffer_data[(i * width + j) * 20 + 12] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 13] = 0.5f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 14] = 0.5f;



					  //v4
					  g_vertex_buffer_data[(i * width + j) * 20 + 15] = interpolate(x, 0, WIDTH, -1, 1);
					  g_vertex_buffer_data[(i * width + j) * 20 + 16] = interpolate(y + Parameters::PixelSize, 0, HEIGHT, 1, -1);

					  //c4
					  g_vertex_buffer_data[(i * width + j) * 20 + 17] = 1.0f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 18] = 1.0f;
					  g_vertex_buffer_data[(i * width + j) * 20 + 19]= 1.0f;*/
			}
		}

	}
	void Refresh()
	{
		//TOD seperate view port
		//glViewport(0, 0, viewWidth, viewHeight);
		glBufferData(GL_ARRAY_BUFFER, height*width * 28 * sizeof(GLfloat), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	}
	void InitializeBuffer()
	{
		// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	   //  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		ptrRCube->BindDensity(g_vertex_buffer_data, 3, Parameters::BackGroundColorR, Parameters::PrimaryColorR);
		ptrGCube->BindDensity(g_vertex_buffer_data, 4, Parameters::BackGroundColorG, Parameters::PrimaryColorG);
		ptrBCube->BindDensity(g_vertex_buffer_data, 5, Parameters::BackGroundColorB, Parameters::PrimaryColorB);
		ptrACube->BindDensity(g_vertex_buffer_data, 6, Parameters::BackGroundColorA, Parameters::PrimaryColorA);

		//ptrCube->BindDensity(g_vertex_buffer_data, 3, Parameters::BackGroundColorR, Parameters::PrimaryColorR);
		//ptrRCube->SetBounds(Parameters::BackGroundColorR,Parameters::PrimaryColorR);
		glGenBuffers(1, &vertexbuffer);

		LOG("vertexbuffer::%d", vertexbuffer)

			//glGenBuffers(2, &vertexbuffer[0]);
			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, height*width * 28 * sizeof(GLfloat), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		LOG("program::%d", Shader::program)
			LOG("sizeof(g_vertex_buffer_data)::%d", sizeof(g_vertex_buffer_data))
			mvp_location = glGetUniformLocation(Shader::program, "MVP");
		vpos_location = glGetAttribLocation(Shader::program, "vPos");
		vcol_location = glGetAttribLocation(Shader::program, "vCol");
		LOG("mvp_location::%d", mvp_location);
		LOG("vpos_location::%d", vpos_location);
		LOG("vcol_location::%d", vcol_location);
		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
		glEnableVertexAttribArray(vcol_location);

		glVertexAttribPointer(vcol_location, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
		mat4x4_identity(m);
	}
	void draw()
	{

		// float ratio;
		//int width = Parameters::Width, height = Parameters::Height;
		//vec4 m[4], p[4], mvp[4];
		
		//ratio = width / (float)height;
		
		//  mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		  //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		  //mat4x4_mul(mvp, p, m);
		  //mat4x4_mul(mvp, m, m);
		//glClear(GL_COLOR_BUFFER_BIT);
		
		//	  glUseProgram(Shader::program);
		//	  LOG("%s","def")
			  //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)m);
		
		glDrawArrays(GL_QUADS, 0, height*width * 4);

		/*	  for (int i = 0;i < HEIGHT / Parameters::PixelSize;i++)
				  for (int j = 0;j < WIDTH / Parameters::PixelSize;j++)
					  changePixelColor(j, i, 0.0f, ptrCube->getDensity(j, i),0.0f, 0.5f);
			*/

		ptrRCube->FluidCubeStep();
		ptrGCube->FluidCubeStep();
		ptrBCube->FluidCubeStep();
		ptrACube->FluidCubeStep();
		
		//ptrCube->FluidCubeStep();
		Refresh();
	}
	void changePixelColor(int locx, int locy, float r, float g, float b, float a)
	{
		//  int x = j * Parameters::PixelSize;
		//  int y = i * Parameters::PixelSize;

		int j = locx;
		int i = locy;
		//x++;y++;
		//v1
	  //  g_vertex_buffer_data[(i * width + j) * 28] = interpolate(x, 0, WIDTH, -1, 1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 1] = interpolate(y, 0, HEIGHT, 1, -1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 2] = 0.0f;
		//c1
		g_vertex_buffer_data[(i * width + j) * 28 + 3] = r;
		g_vertex_buffer_data[(i * width + j) * 28 + 4] = g;
		g_vertex_buffer_data[(i * width + j) * 28 + 5] = b;
		g_vertex_buffer_data[(i * width + j) * 28 + 6] = a;

		//v2
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 7] = interpolate(x + Parameters::PixelSize, 0, WIDTH, -1, 1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 8] = interpolate(y, 0, HEIGHT, 1, -1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 9] = 0.0f;
		//c2
		g_vertex_buffer_data[(i * width + j) * 28 + 10] = r;
		g_vertex_buffer_data[(i * width + j) * 28 + 11] = g;
		g_vertex_buffer_data[(i * width + j) * 28 + 12] = b;
		g_vertex_buffer_data[(i * width + j) * 28 + 13] = a;


		//v3
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 14] = interpolate(x + Parameters::PixelSize, 0, WIDTH, -1, 1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 15] = interpolate(y + Parameters::PixelSize, 0, HEIGHT, 1, -1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 16] = 0.0f;
		//c3
		g_vertex_buffer_data[(i * width + j) * 28 + 17] = r;
		g_vertex_buffer_data[(i * width + j) * 28 + 18] = g;
		g_vertex_buffer_data[(i * width + j) * 28 + 19] = b;
		g_vertex_buffer_data[(i * width + j) * 28 + 20] = a;


		//v4
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 21] = interpolate(x, 0, WIDTH, -1, 1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 22] = interpolate(y + Parameters::PixelSize, 0, HEIGHT, 1, -1);
  //	  g_vertex_buffer_data[(i * width + j) * 28 + 23] = 0.1f;
		//c4
		g_vertex_buffer_data[(i * width + j) * 28 + 24] = r;
		g_vertex_buffer_data[(i * width + j) * 28 + 25] = g;
		g_vertex_buffer_data[(i * width + j) * 28 + 26] = b;
		g_vertex_buffer_data[(i * width + j) * 28 + 27] = a;
		glBufferData(GL_ARRAY_BUFFER, height*width * 28 * sizeof(GLfloat), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

		//LOG("b::%0.9f",b)
	}
	void AddMovementPrimary(int x, int y, float dx, float dy)
	{
		/*ptrRCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::PrimaryColorR);
		ptrRCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrGCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::PrimaryColorG);
		ptrGCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrBCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::PrimaryColorB);
		ptrBCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrACube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize,  Parameters::PrimaryColorA);
		ptrACube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);
		*/
		
		ptrRCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorR - Parameters::PrimaryColorR) * Parameters::DensityAmount);
		ptrRCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrGCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorG - Parameters::PrimaryColorG) * Parameters::DensityAmount);
		ptrGCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrBCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorB - Parameters::PrimaryColorB) * Parameters::DensityAmount);
		ptrBCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrACube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorA - Parameters::PrimaryColorA) * Parameters::DensityAmount);
		ptrACube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);
		
	}
	void AddMovementSecondary(int x, int y, float dx, float dy)
	{
		/*ptrRCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::SecondaryColorR);
		ptrRCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);	
																										
		ptrGCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::SecondaryColorG);
		ptrGCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);	
																										
		ptrBCube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::SecondaryColorB);
		ptrBCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);	
																										
		ptrACube->FluidCubeSetDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, Parameters::SecondaryColorA);
		ptrACube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		*/
		ptrRCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorR - Parameters::SecondaryColorR) * Parameters::DensityAmount);
		ptrRCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrGCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorG - Parameters::SecondaryColorG) * Parameters::DensityAmount);
		ptrGCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrBCube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorB - Parameters::SecondaryColorB) * Parameters::DensityAmount);
		ptrBCube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);

		ptrACube->FluidCubeAddDensity(x / Parameters::PixelSize, y / Parameters::PixelSize, -(Parameters::BackGroundColorA - Parameters::SecondaryColorA) * Parameters::DensityAmount);
		ptrACube->FluidCubeAddVelocity(x / Parameters::PixelSize, y / Parameters::PixelSize, dx, dy);
	
	}
};

#endif PIXELGRID_H

