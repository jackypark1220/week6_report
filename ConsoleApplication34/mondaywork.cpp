#define d_SCL_SECURE_NO_WARNINGS
#include <glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include<algorithm>
#include<Windows.h>
#include<vector>
const int width = 1180;
const int height = 490;

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

double getRandouble(const double min, const double max) {
	double temp = ((double)rand()) / (double)RAND_MAX;
	temp = min + (max - min)*temp;
	return temp;
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
				drawPixel(x - g + b, y - g + a, 255, 255, 255);
			}
		}
	}
}
bool isinsideCircle(const double x, const double y, const double x_c , const double y_c , const double r_c ) {
	double f = (x - x_c)*(x - x_c) + (y - y_c)* (y - y_c) - r_c*r_c;
	if (f <= 0)
		return true;
	else return false;
}
void drawcircle(const int x, const int y, const int r)
{
	for (int i = 0; i <= 360; i++) {
		drawPixel(x + r * cos(i), y + r * sin(i), 255, -255, -255);
	}
}
void colorcircle(const int x, const int y, const int r)
{
	for (int i = 0; i <= 360; i++) {
		drawPixel(x + r * cos(i), y + r * sin(i), 0, 0, 0);
	}
}

void drawOnPixelBuffer()
{
	fflush(stdin);
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;
	//drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);

	//TODO: try moving object
	
	
	/*drawrectanful(850, 850, 100, 0, 0, 100);
	drawrectanline(250, 250, 100, 250, 0, 0);
	drawthick(500, 800, 700, 900, 0, 255, 255);
	drawtri(500, 100, 650, 400, 800, 100, 255, 0, 0);
	drawpenta(600, 550, 550, 650, 650, 720, 750, 650, 700, 550, 255, 0, 0);*/
}

class DrawInCircle
{
public:
	void draw()
	{
		drawcircle(500,300,50);
	}
};

class DrawBox
{
public:
	void draw()
	{
		drawrectanline(200, 155, 100, 255, 255, 0);
	}
};
class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
};

template<class T_HOW_TO_DRAW>
class GeometricObject : public GeometricObjectInterface

{
public:
	void draw()
	{
		T_HOW_TO_DRAW draw_in_color;
		draw_in_color.draw();
	}
};
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
			double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				printf("%f, %f\n", xpos, ypos);

				


				std::vector<GeometricObjectInterface*> obj_list;
				obj_list.push_back(new GeometricObject<DrawInCircle>);
				obj_list.push_back(new GeometricObject<DrawBox>);

				for (auto itr : obj_list)
				{
					itr->draw();
				}



			//TODO: RGB struct
			//Make a pixel drawing function
			//Make a line drawing function

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