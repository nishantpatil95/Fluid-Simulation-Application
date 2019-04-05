#include "pch.h"
#include "Fluid2D.h"


Fluid2D::Fluid2D(int size_w, int size_h, float *diffusion, float *vicosity, float *dt)
{
	W = size_w;
	H = size_h;
	this->size_w = size_w;
	this->size_h = size_h;
	this->dt = dt;
	this->diff = diffusion;
	this->visc = vicosity;
	this->s = (float*)calloc(W * H, sizeof(float));
	this->density = new Density[W * H];
	this->Vx = (float*)calloc(W * H, sizeof(float));
	this->Vy = (float*)calloc(W * H, sizeof(float));
	this->Vx0 = (float*)calloc(W * H, sizeof(float));
	this->Vy0 = (float*)calloc(W * H, sizeof(float));

}
Fluid2D::~Fluid2D()
{
	FluidCubeFree();
}
void Fluid2D::BindDensity(float *g_vertex_buffer_data, int loc, float bg, float pri)
{
	for (int i = 0;i < H;i++)
	{
		for (int j = 0;j < W;j++)
		{
			//	LOG("i::%d j::%d %x bind to %x", i, j, &g_vertex_buffer_data[(i * W + j) * 28 + 3], &density[IX(j, i)])
			this->density[IX(j, i)].bind(&g_vertex_buffer_data[(i * W + j) * 28 + loc]);
			//this->density[IX(j, i)].Bound(bg,pri);
		}
	}
}
void Fluid2D::FluidCubeFree()
{
	free(this->s);
	free(this->density);
	free(this->Vx);
	free(this->Vy);
	free(this->Vx0);
	free(this->Vy0);

}
void Fluid2D::FluidCubeAddDensity(int x, int y, float amount)
{
	(this->density[IX(x, y)]).increment(amount);
}
void Fluid2D::FluidCubeSetDensity(int x, int y, float amount)
{
	(this->density[IX(x, y)]).set(amount);
}

void Fluid2D::FluidCubeAddVelocity(int x, int y, float amountX, float amountY)
{

	//int index = IX(x, y);

	this->Vx[IX(x, y)] += amountX;
	this->Vy[IX(x, y)] += amountY;


}
void Fluid2D::diffuse(int b, float *x, Density *x0, float diff, float dt)//my function
{
	float a = dt * diff * (W - 2) * (H - 2);
	lin_solve(b, x, x0, a, 1 + 6 * a);
}
void Fluid2D::diffuse(int b, float *x, float *x0, float diff, float dt)
{
	float a = dt * diff * (W - 2) * (H - 2);
	lin_solve(b, x, x0, a, 1 + 6 * a);
}
void Fluid2D::lin_solve(int b, float *x, Density *x0, float a, float c)
{
	float cRecip = 1.0 / c;
	for (int k = 0; k < iter; k++) {

		for (int j = 1; j < H - 1; j++) {
			for (int i = 1; i < W - 1; i++) {
				x[IX(i, j)] =
					(x0[IX(i, j)].getVal()
						+ a * (x[IX(i + 1, j)]
							+ x[IX(i - 1, j)]
							+ x[IX(i, j + 1)]
							+ x[IX(i, j - 1)]
							)) * cRecip;
			}
		}

		set_bnd(b, x);
	}
}
void  Fluid2D::lin_solve(int b, float *x, float *x0, float a, float c)
{
	float cRecip = 1.0 / c;
	for (int k = 0; k < iter; k++) {

		for (int j = 1; j < H - 1; j++) {
			for (int i = 1; i < W - 1; i++) {
				x[IX(i, j)] =
					(x0[IX(i, j)]
						+ a * (x[IX(i + 1, j)]
							+ x[IX(i - 1, j)]
							+ x[IX(i, j + 1)]
							+ x[IX(i, j - 1)]

							)) * cRecip;
			}
		}
		set_bnd(b, x);
	}
}
void Fluid2D::project(float *velocX, float *velocY, float *p, float *div)
{

	for (int j = 1; j < H - 1; j++) {
		for (int i = 1; i < W - 1; i++) {
			div[IX(i, j)] = -0.5f*(
				velocX[IX(i + 1, j)]
				- velocX[IX(i - 1, j)]
				+ velocY[IX(i, j + 1)]
				- velocY[IX(i, j - 1)]

				) / W;
			p[IX(i, j)] = 0;
		}
	}
	set_bnd(0, div);
	set_bnd(0, p);
	lin_solve(0, p, div, 1, 6);
	for (int j = 1; j < H - 1; j++) {
		for (int i = 1; i < W - 1; i++) {
			velocX[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)]
				- p[IX(i - 1, j)]) * W;
			velocY[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)]
				- p[IX(i, j - 1)]) * W;

		}
	}
	set_bnd(1, velocX);
	set_bnd(2, velocY);
}
void Fluid2D::advect(int b, float *d, float *d0, float *velocX, float *velocY, float dt)
{
	//LOG("%0.9f",*d)
	float i0, i1, j0, j1;

	float dtx = dt * (W - 2);
	float dty = dt * (H - 2);

	float s0, s1, t0, t1;
	float tmp1, tmp2, x, y;

	float Wfloat = W;
	float Hfloat = H;
	float ifloat, jfloat;
	int i, j;

	int i0i, i1i, j0i, j1i;

	for (j = 1, jfloat = 1; j < H - 1; j++, jfloat++) {
		for (i = 1, ifloat = 1; i < W - 1; i++, ifloat++) {
			tmp1 = dtx * velocX[IX(i, j)];
			tmp2 = dty * velocY[IX(i, j)];

			x = ifloat - tmp1;
			y = jfloat - tmp2;


			if (x < 0.5f) x = 0.5f;
			if (x > Wfloat + 0.5f) x = Wfloat + 0.5f;
			i0 = floorf(x);
			i1 = i0 + 1.0f;
			if (y < 0.5f) y = 0.5f;
			if (y > Hfloat + 0.5f) y = Hfloat + 0.5f;
			j0 = floorf(y);
			j1 = j0 + 1.0f;

			s1 = x - i0;
			s0 = 1.0f - s1;
			t1 = y - j0;
			t0 = 1.0f - t1;


			 i0i = constaint(i0, 0, W - 1);
			 i1i = constaint(i1, 0, W - 1);
			 j0i = constaint(j0, 0, H - 1);
			 j1i = constaint(j1, 0, H - 1);

			d[IX(i, j)] =

				s0 * ((t0 *  d0[IX(i0i, j0i)])
					+ (t1 *  d0[IX(i0i, j1i)]))
				+ s1 * ((t0 *  d0[IX(i1i, j0i)])
					+ (t1 *  d0[IX(i1i, j1i)]));
		}
	}

	set_bnd(b, d);
}
void Fluid2D::advect(int b, Density *d, float *d0, float *velocX, float *velocY, float dt)//my function
{
	float i0 = 0.0f, i1 = 0.0f, j0 = 0.0f, j1 = 0.0f;

	float dtx = dt * (W - 2);
	float dty = dt * (H - 2);

	float s0 = 0.0f, s1 = 0.0f, t0 = 0.0f, t1 = 0.0f;
	float tmp1 = 0.0f, tmp2 = 0.0f, x = 0.0f, y = 0.0f;

	float Hfloat = H;
	float Wfloat = W;
	float ifloat, jfloat;
	int i, j;

	int i0i, i1i, j0i, j1i;

	for (j = 1, jfloat = 1; j < H - 1; j++, jfloat++) {
		for (i = 1, ifloat = 1; i < W - 1; i++, ifloat++) {
			tmp1 = dtx * velocX[IX(i, j)];
			tmp2 = dty * velocY[IX(i, j)];

			x = ifloat - tmp1;
			y = jfloat - tmp2;


			if (x < 0.5f) x = 0.5f;
			if (x > Wfloat + 0.5f) x = Wfloat + 0.5f;
			i0 = floorf(x);
			i1 = i0 + 1.0f;
			if (y < 0.5f) y = 0.5f;
			if (y > Hfloat + 0.5f) y = Hfloat + 0.5f;
			j0 = floorf(y);
			j1 = j0 + 1.0f;

			s1 = x - i0;
			s0 = 1.0f - s1;
			t1 = y - j0;
			t0 = 1.0f - t1;

			i0i = constaint(i0, 0, W - 1);
			i1i = constaint(i1, 0, W - 1);
			j0i = constaint(j0, 0, H - 1);
			j1i = constaint(j1, 0, H - 1);
			

			d[IX(i, j)].set(

				s0 * ((t0 *  d0[IX(i0i, j0i)])
					+ (t1 *  d0[IX(i0i, j1i)]))
				+ s1 * ((t0 *  d0[IX(i1i, j0i)])
					+ (t1 *  d0[IX(i1i, j1i)])));



		}
	}

	set_bnd(b, d);

}

void Fluid2D::set_bnd(int b, Density *x)//my 
{
	for (int i = 1;i < W - 1;i++)
	{
		x[IX(i, 0)].set(b == 2 ? -x[IX(i, 1)].getVal() : x[IX(i, 1)].getVal());
		x[IX(i, H - 1)].set(b == 2 ? -x[IX(i, H - 2)].getVal() : x[IX(i, H - 2)].getVal());
	}
	for (int j = 1;j < H - 1;j++)
	{
		x[IX(0, j)].set(b == 1 ? -x[IX(1, j)].getVal() : x[IX(1, j)].getVal());
		x[IX(W - 1, j)].set(b == 1 ? -x[IX(W - 2, j)].getVal() : x[IX(W - 2, j)].getVal());
	}
	x[IX(0, 0)].set(0.5f*(x[IX(1, 0)].getVal() + x[IX(0, 1)].getVal()));
	x[IX(0, H - 1)].set(0.5f*(x[IX(1, H - 1)].getVal() + x[IX(0, H - 2)].getVal()));
	x[IX(W - 1, 0)].set(0.5f*(x[IX(W - 2, 0)].getVal() + x[IX(W - 1, 1)].getVal()));
	x[IX(W - 1, H - 1)].set(0.5f*(x[IX(W - 2, H - 1)].getVal() + x[IX(W - 1, H - 2)].getVal()));
}
void Fluid2D::set_bnd(int b, float *x)
{
	for (int i = 1;i < W - 1;i++)
	{
		x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
		x[IX(i, H - 1)] = b == 2 ? -x[IX(i, H - 2)] : x[IX(i, H - 2)];
	}
	for (int j = 1;j < H - 1;j++)
	{
		x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
		x[IX(W - 1, j)] = b == 1 ? -x[IX(W - 2, j)] : x[IX(W - 2, j)];
	}
	x[IX(0, 0)] = 0.5f*(x[IX(1, 0)] + x[IX(0, 1)]);
	x[IX(0, H - 1)] = 0.5f*(x[IX(1, H - 1)] + x[IX(0, H - 2)]);
	x[IX(W - 1, 0)] = 0.5f*(x[IX(W - 2, 0)] + x[IX(W - 1, 1)]);
	x[IX(W - 1, H - 1)] = 0.5f*(x[IX(W - 2, H - 1)] + x[IX(W - 1, H - 2)]);

}
void Fluid2D::FluidCubeStep()
{

	/*float *visc = this->visc;
	float *diff = this->diff;
	float *dt = this->dt;
	float *Vx = this->Vx;
	float *Vy = this->Vy;

	float *Vx0 = this->Vx0;
	float *Vy0 = this->Vy0;

	float *s = this->s;
	Density *density = this->density;
	*/
	diffuse(1, Vx0, Vx, *visc, *dt);
	diffuse(2, Vy0, Vy, *visc, *dt);

	project(Vx0, Vy0, Vx, Vy);

	advect(1, Vx, Vx0, Vx0, Vy0, *dt);
	advect(2, Vy, Vy0, Vx0, Vy0, *dt);

	project(Vx, Vy, Vx0, Vy0);

	diffuse(0, s, density, *diff, *dt);
	advect(0, density, s, Vx, Vy, *dt);
}
