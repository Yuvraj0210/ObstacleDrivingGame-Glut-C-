#pragma once
#ifndef TREE_H
#define TREE_H

class Tree {

	float x, y;
public:
	Tree();
	Tree(float a, float b);
	void change(float a, float b);
	void changeX(float a);
	void changeY();
	int getX();
	int getY() ;
};
#endif
