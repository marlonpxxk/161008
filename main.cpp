#include "draw.h"
#include <iostream>

int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "ICON WORLD!", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	
	//get cursor position
	glfwGetCursorPos(window, &cursor_x, &cursor_y);
	cursor_y = height - cursor_y; // this is because GetCursorPos's y coordinates is inverted.
	
	
	//cursor position callback not used.
	//glfwSetCursorPosCallback(window, cursorPositionCallBack);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		drawOnPixelBuffer();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

void Icon::setAreaArray(int x, int y)
{
	coordinates[(x + width* y) * 2 + 0] = (float)x;
	coordinates[(x + width* y) * 2 + 1] = (float)y;
}

void Icon::initAreaArray()
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{

			const int _x = c_x, _y = c_y;
			const int _r = c_r;
			const int _w = c_w;

			//if in circle area,
			if (sqrt((_x - a)*(_x - a) + (_y - b)*(_y - b)) <= _r)
			{
				//save the coordinates
				setAreaArray(a, b);
			}
		}
	}
}

void Icon::SetIconCoordinates(const int x, const int y, const int r, const int w)
{
	c_x = x;
	c_y = y;
	c_r = r;
	c_w = w;
}

float Icon::PullAreaX(int x, int y) const
{
	return coordinates[(x + width* y) * 2 + 0];
}

float Icon::PullAreaY(int x, int y) const
{
	return coordinates[(x + width* y) * 2 + 1];
}


int Icon::PullIconX() const
{
	return c_x;
}

int Icon::PullIconY() const
{
	return c_y;
}

int Icon::PullIconR() const
{
	return c_r;
}

int Icon::PullIconW() const
{
	return c_w;
}


//this function is not used yet. Shows current cursor's coordinates
static void cursorPositionCallBack(GLFWwindow *window, double xPos, double yPos)
{
	cursor_x = xPos;
	cursor_y = height - yPos; // because CursorPosition's  y coordinates is inverted! (the most upper y is considered 0)

	std::cout << cursor_x << " " << cursor_y << std::endl;
}


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

//determine if the coordinates matches the Circle Icon's inside area
void checkIconArea(Icon icon)
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			float icon_x = icon.PullAreaX(a, b);
			float icon_y = icon.PullAreaY(a, b);
			if (icon_x == cursor_x
				&& icon_y == cursor_y)
				//if coordinates matches, convert the outer circle color to blue
				drawCircle(icon.PullIconX(), icon.PullIconY(), icon.PullIconR(), icon.PullIconW(), 0.0f, 0.0f, 1.0f);
		}
	}
}


// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i1 == i0) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
	for (int i = i0; i <= i1; i++) {
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background


	line.SetIconCoordinates(100, 650, 50, 3);
	circ.SetIconCoordinates(250, 650, 50, 3);
	squa.SetIconCoordinates(400, 650, 50, 3);
	X.SetIconCoordinates(550, 650, 50, 3);
	A.SetIconCoordinates(700, 650, 50, 3);

	up.SetIconCoordinates(100, 450, 50, 3);
	down.SetIconCoordinates(250, 450, 50, 3);
	right.SetIconCoordinates(400, 450, 50, 3);
	left.SetIconCoordinates(550, 450, 50, 3);
	vert.SetIconCoordinates(700, 450, 50, 3);


	//draw icons
	//first top row
	drawLineICON(line);
	drawCirclularICON(circ);
	drawSquareICON(squa);
	drawXICON(X);
	drawVerticalICON(vert);


	//second bottom row
	drawDownICON(down);
	drawUpICON(up);
	drawRightICON(right);
	drawLeftICON(left);
	drawAICON(A);
}

//w is the width of the circle'outer shell
void drawCircle(const int x, const int y, const int r, const int w, const float red, const float green, const float blue)
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			
			if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) <= r)
			{
				if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) >= r - w)
					drawPixel(a, b, red, green, blue);
			}
		}
	}
}

void drawLineICON(Icon icon)
{
	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw inner Line mark
	for (int i = 0; i < 5; i++) {
		drawLine((x - (r / 2)) - i, (y - (r / 2)) + i, (x + (r / 2)) - i, (y + (r / 2)) + i, 1.0f, 0.0f, 0.0f);
	}

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawXICON(Icon icon)
{
	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw inner X mark
	for (int i = 0; i < 5; i++) {
		drawLine((x - (r / 2)) - i, (y - (r / 2)) + i, (x + (r / 2)) - i, (y + (r / 2)) + i, 1.0f, 0.0f, 0.0f);
		drawLine((x - (r / 2)) + i, (y + (r / 2)) + i, (x + (r / 2)) + i, (y - (r / 2)) + i, 1.0f, 0.0f, 0.0f);
	}

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawCirclularICON(Icon icon)
{
	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw inner circle (more bold width, smaller the radius)
	drawCircle(x, y, (2 * r / 5), w + 4, 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawSquareICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw inner Square
	drawLine((x - (r / 2)), (y - (r / 2)), (x - (r / 2)), (y + (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine((x - (r / 2)), (y - (r / 2)), (x + (r / 2)), (y - (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine((x - (r / 2)), (y + (r / 2)), (x + (r / 2)), (y + (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine((x + (r / 2)), (y - (r / 2)), (x + (r / 2)), (y + (r / 2)), 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawDownICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw down arrow
	drawLine(x, (y - (r / 2)), x, (y + (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine(x, (y - (r / 2)), (x + (r / 4)), (y - (r / 4)), 1.0f, 0.0f, 0.0f);
	drawLine(x - (r / 4), (y - (r / 4)), x, (y - (r / 2)), 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawUpICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw upper arrow
	drawLine(x, (y - (r / 2)), x, (y + (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine(x, (y + (r / 2)), (x + (r / 4)), (y + (r / 4)), 1.0f, 0.0f, 0.0f);
	drawLine(x - (r / 4), (y + (r / 4)), x, (y + (r / 2)), 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawRightICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw right arrow
	drawLine((x - (r / 2)), y, (x + (r / 2)), y, 1.0f, 0.0f, 0.0f);
	drawLine((x + (r / 4)), (y + (r / 4)), (x + (r / 2)), y, 1.0f, 0.0f, 0.0f);
	drawLine((x + (r / 4)), (y - (r / 4)), (x + (r / 2)), y, 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawLeftICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw left arrow
	drawLine((x - (r / 2)), y, (x + (r / 2)), y, 1.0f, 0.0f, 0.0f);
	drawLine((x - (r / 2)), y, (x - (r / 4)), (y + (r / 4)), 1.0f, 0.0f, 0.0f);
	drawLine((x - (r / 2)), y, (x - (r / 4)), (y - (r / 4)), 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawVerticalICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw vertical line
	drawLine(x, (y - (r / 2)), x, (y + (r / 2)), 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}

void drawAICON(Icon icon)
{

	//initialize saving icon area's coordinates in array
	icon.initAreaArray();

	//get icon's x,y,r,w info
	const int x = icon.PullIconX();
	const int y = icon.PullIconY();
	const int r = icon.PullIconR();
	const int w = icon.PullIconW();

	//draw outer circle
	drawCircle(x, y, r, w, 1.0f, 0.0f, 0.0f);

	//draw A shape
	drawLine((x - (r / 2)), (y - (r / 2)), x, (y + (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine(x, (y + (r / 2)), (x + (r / 2)), (y - (r / 2)), 1.0f, 0.0f, 0.0f);
	drawLine((x - (r / 4)), y, (x + (r / 4)), y, 1.0f, 0.0f, 0.0f);

	//check if the cursor is inside the icon area
	checkIconArea(icon);
}
