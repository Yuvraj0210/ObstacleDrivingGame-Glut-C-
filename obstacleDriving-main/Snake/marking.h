#pragma once

#ifndef MARKING_H
#define MARKING_H

class Marking {
	float x, y;
public:
	Marking() {
		x = 0;
		y = 0;
	}
	void change(float a,float b) {
		x = a;
		y = b;
	}
	void changeY() {
		y=y-1;
		if (y < -6) {
			y = 63.5;
		}
	}
	float getX() {
		return x;
	}

	float getY() {
		return y;
	}
};
#endif
