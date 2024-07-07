#pragma once

#ifndef CAR_H
#define CAR_H

#include "stb_image.h"


class Car {
	float x, y;
public:
	Car() {
		x = 0; y = 0;
	}
	void change(float a, float b) {
		x = a, y = b;
	}
	
	void steerRight() {
		x =x+3;

	}
	void steerLeft() {
		x =x-3;

	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}


};

#endif


