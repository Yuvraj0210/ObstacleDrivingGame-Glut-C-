#include "tree.h"

Tree::Tree() {
	x = 0.0; y = 0.0;
}
Tree::Tree(float a, float b) {
x = a;
y = b;
}
void Tree :: change(float a, float b) {
	x = a;
	y = b;
}
void Tree::changeX(float a) {
	x = a;
}
void Tree::changeY() {
	y=y-1;
	if (y < 0) {
		y = 60;
	}
}
int Tree::getX() {
	return x;
}
int Tree::getY() {
	return y;
}

