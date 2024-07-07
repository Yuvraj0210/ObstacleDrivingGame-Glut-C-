#pragma once

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
	float x,y;
public:
	Obstacle() {
		x = 0; y = 0;
	}
	Obstacle(float a, float b) {
		x = a, y = b;
	}
	void change(float a,float b) {
		x = a; y = b;

	}
	void changeY() {
		y = y - 1;
	}
	float getX() {
		return x;

	}
	float getY() {
		return y;
	}
	
};

#endif
