#pragma once
#ifndef GAME_H
#define GAME_H

#define LEFT 1
#define MIDDLE 3
#define RIGHT 2
#define RIGHTSTOP -2
#define LEFTSTOP -1



#include "tree.h"
#include "marking.h"
#include "car.h"
#include "stb_image.h"
#include "obstacle.h"
#include "bullet.h"


void initGrid(int, int);
void drawGrid();
void drawSky();
void unit(int x, int y);
void drawSnake();
void drawTree(Tree obj);
void drawGrass();
void drawRoad();
void initMarking();
void drawMarking();
void drawCar();
void drawObstacle();
void initObstacle();
void initBullet();
void drawBullet();
void drawExplosion();
void collisionDetection();
void showScore();
void finalScore();
void finalScore2();
//void drawCircle(float x,float y,float radius);

#endif
