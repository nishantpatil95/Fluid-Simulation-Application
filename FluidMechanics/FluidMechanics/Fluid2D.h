#include "pch.h"
#define IX(x, y) ((x) + (y) * W )

class Density
{
public:
	float * loc1;
	float * loc2;
	float * loc3;
	float * loc4;

	void bind(float * ptr)
	{
		//	LOG("%x is bind to %x", ptr, loc1);
		loc1 = ptr;
		loc2 = ptr + 7;
		loc3 = ptr + 14;
		loc4 = ptr + 21;
	}

	
	void increment(float& val)
	{
		//	set(constaint(*this->loc1 + val, bg, pri));
		set(*this->loc1 + val);
		
	}
	float getVal()
	{
		//LOG("req %x",this)
		return *loc1;
	}
	void set(float val)
	{
		//val = constaint(val, 0.0f, 10.0f);
		*this->loc1 = val;
		*this->loc2 = val;
		*this->loc3 = val;
		*this->loc4 = val;
	}
};



class Fluid2D {
private:
	//int size;
	//int N;

	int size_w;
	int size_h;

	int W;
	int H;

	int iter = 10;
	float *dt;
	float *diff;
	float *visc;

	float *s;
	//float **density;

	Density *density;

	float *Vx;
	float *Vy;


	float *Vx0;
	float *Vy0;


public:

	Fluid2D(int size_w, int size_h, float *diffusion, float *vicosity, float *dt);
	
	void BindDensity(float *g_vertex_buffer_data, int loc, float bg, float pri);
	
	void FluidCubeFree();
	~Fluid2D();

	void FluidCubeAddDensity(int x, int y, float amount);
	
	void FluidCubeSetDensity(int x, int y, float amount);
	
	void FluidCubeAddVelocity(int x, int y, float amountX, float amountY);

	void diffuse(int b, float *x, Density *x0, float diff, float dt);//my function
	
	void diffuse(int b, float *x, float *x0, float diff, float dt);

	void lin_solve(int b, float *x, Density *x0, float a, float c);
	
	void lin_solve(int b, float *x, float *x0, float a, float c);

	void project(float *velocX, float *velocY, float *p, float *div);
	
	void advect(int b, float *d, float *d0, float *velocX, float *velocY, float dt);
	
	void advect(int b, Density *d, float *d0, float *velocX, float *velocY, float dt);//my function
	
	void set_bnd(int b, Density *x);//my 
	
	void set_bnd(int b, float *x);
	
	void FluidCubeStep();
	


};
typedef struct FluidCube FluidCube;