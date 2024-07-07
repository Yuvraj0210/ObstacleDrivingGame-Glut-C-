#pragma once
#ifndef BULLET_H
#define BULLET_H


class Bullet {
	float x, y;
public:
	Bullet() {
		x = 0; y = 0;
	}
	Bullet(float a, float b) {
		x = a; y = b;
	}
	~Bullet() {

	}
	void change(float a, float b) {
		x = a; y = b;
	}
	void changeY() {
		y++;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
};


#endif
