#pragma once
#ifndef __DRAW_H__
#define __DRAW_H__

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

//Canvas Size
const int width = 1024;
const int height = 768;

//coordinates of Mouse Cursor
double cursor_x = 0;
double cursor_y = 0;

//Pixel Array
float* pixels = new float[width * height * 3];


class Icon
{
private:
	int c_x, c_y, c_r, c_w; //x, y, radious, width
	float* coordinates = new float[width * height * 2]; //storing internal x, y coordinates of an icon
public:
	void setAreaArray(int x, int y);
	void initAreaArray();
	void SetIconCoordinates(const int x, const int y, const int r, const int w);
	float PullAreaX(int x, int y) const;
	float PullAreaY(int x, int y) const;
	int PullIconX() const;
	int PullIconY() const;
	int PullIconR() const;
	int PullIconW() const;
};

//function predefinition
static void cursorPositionCallBack(GLFWwindow *window, double xPos, double yPos);
void drawCircle(const int x, const int y, const int r, const int w, const float red, const float green, const float blue);
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawOnPixelBuffer();


//functions using Icon Class
void checkIconArea(Icon icon);
void drawLineICON(Icon icon);
void drawXICON(Icon icon);
void drawSquareICON(Icon icon);
void drawCirclularICON(Icon icon);
void drawUpICON(Icon icon);
void drawDownICON(Icon icon);
void drawRightICON(Icon icon);
void drawLeftICON(Icon icon);
void drawVerticalICON(Icon icon);
void drawAICON(Icon icon);
#endif