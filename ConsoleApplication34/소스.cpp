#define d_SCL_SECURE_NO_WARNINGS
#include <glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include<algorithm>

const int width = 1000;
const int height = 1000;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawtri(const int& i, const int& j, const int& a, const int& b, const int& k, const int& l ,const float& red, const float& green, const float& blue)
{
	drawLine(i, j, a, b, red, green, blue);
	drawLine(a, b, k, l, red, green, blue);
	drawLine(i,j ,k , l, red, green, blue);
	//250,500¿¡¼­ Á¡
	//249,499
}
void drawpenta(const int& i, const int& j, const int& a, const int& b, const int& k, const int& l, const int& o, const int& p, const int& q, const int& r,const float& red, const float& green, const float& blue)
{
	drawLine(a,b,i,j, red, green, blue);
	drawLine(a, b, k, l, red, green, blue);
	drawLine(k,l,o,p, red, green, blue);
	drawLine(q,r,o,p,  red, green, blue);
	drawLine(i, j, q, r, red, green, blue);
}
double getRandouble(const double min, const double max) {
	double temp = ((double)rand()) / (double)RAND_MAX;
	temp = min + (max - min)*temp;
	return temp;
}
bool isinsideCircle(const double x, const double y, const double x_c = 25, const double y_c = 25, const double r_c = 25) {
	return (x - x_c)*(x - x_c) + (y - y_c)* (y - y_c) <= r_c*r_c;
}

void drawcircle(const int x, const int y, const int r, const float& red, const float& green, const float& blue)
{
	int x_c = x;
	int y_c = y;


	for (int a = 0; a <= 2 * r; a++)
	{
		for (int b = 0; b <= 2 * r; b++)
		{
			int f = (r - b)*(r - b) + (r - a)*(r - a) - r*r;
			if (f < -30&& f>-350)
			{
				drawPixel(x - r + b, y - r + a, 255, 0, 0);
			}
		}
	}
}
void drawrectanline(const int x, const int y, const int r, const float& red, const float& green, const float& blue)
{
	int x_c = x;
	int y_c = y;
	for (int a = 0; a <= 2 * r; a++)
	{
		for (int b = 0; b <= 2 * r; b++)
		{
			{
				drawPixel(x - r + b, y - r + a, red, green, blue);
			}
		}
	}
	int g = (int)r *0.9;
	for (int a = 0; a <= 2 * g; a++)
	{
		for (int b = 0; b <= 2 * g; b++)
		{
			{
				drawPixel(x - g + b, y - g + a, 255, 255,255);
			}
		}
	}
}
void drawthick(const int& i, const int& j, const int& a, const int& b,  const float& red, const float& green, const float& blue)
{
	
	drawLine(i, j, a, b, red, green, blue);
	drawLine(i, j+1, a, b+1, red, green, blue);
	drawLine(i, j+2, a, b+2, red, green, blue);
	drawLine(i, j+3, a, b+3, red, green, blue);
	drawLine(i, j+4, a, b+4, red, green, blue);
	drawLine(i, j+5, a, b+5, red, green, blue);
	
	
}
void drawrectanful(const int x, const int y, const int r, const float& red, const float& green, const float& blue)
{
	int x_c = x;
	int y_c = y;
	for (int a = 0; a <= 2 * r; a++)
	{
		for (int b = 0; b <= 2 * r; b++)
		{
			{
				drawPixel(x - r + b, y - r + a, red,green , blue);
			}
		}
	}
}
void drawlecline(const int& i, const int& j, const int& a, const int& b,const float& red, const float& green, const float& blue)
{
	/*drawLine(i,j,a,b, red, green, blue);
	drawLine(a, b, k, l, red, green, blue);
	drawLine(o,p, k, l, red, green, blue);
	drawLine(i,j, o, p, red, green, blue);
*/
	for (int k = j; k < b; k++) { drawPixel(i, k, 255, 255, 100); }
	for (int k = i; k < a; k++) { drawPixel(k, b, 255, 255, 100); }
	for (int k = b; k > j; k--) { drawPixel(a, k, 255, 255, 100); }
	for (int k = i; k < a; k++) { drawPixel(k, j, 255, 255, 100); }
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;
	drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	 // while background

//register double x, y;
//for (int i = 0; i < 10000; i++) {
//	x = getRandouble(0, 1.0);
//	y = getRandouble(0, 1.0);
//	if (isinsideCircle(x, y))
//		drawPixel(x, y, 1, 0, 0);
//}
							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
	
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();
	drawcircle(250, 750, 150, 255, 0, 0);
	drawrectanful(850, 850, 100, 0, 0, 100);
		drawrectanline(250,250,100,250,0,0);
		drawthick(500,800, 700, 900, 0, 255, 255);
		drawtri(500, 100, 650, 400, 800,100, 255, 0, 0);
		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function
		drawpenta(600, 550, 550, 650, 650, 720, 750, 650, 700, 550,255,0,0);
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		glClearColor(1, 1, 1, 1);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 
	
	return 0;
}