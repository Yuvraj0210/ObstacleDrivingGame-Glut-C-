#include "game.h"
#include<gl/glut.h>
#include "tree.h"
#include "marking.h"
#include <string>
#include <sstream>
#include <iostream>
#include "car.h"
#include "obstacle.h"
#include <queue>
#include<vector>
#include <cstdlib>
#include<stack>
#include "bullet.h"

#include "stb_image.h"

short FPS =60;
short gamePaused = 0;
short crashed = 0;	
short finished = 0;


int score;


int gridX, gridY;

int skyLX, skyLY, skyMX, skyMY;	

int grassLX, grassLY, grassMX, grassMY;

int roadLX, roadLY, roadMX, roadMY;

Tree Tree1, Tree2, Tree3, Tree4;

Marking m1[8],m2[8],m3[8];

Car car;

std::queue<Obstacle> left, right, middle;

std::vector<Obstacle> leftActive, rightActive, middleActive;

std::vector<int> obslist1 = { 3,1,2,2,1,1,2,3,1,1,2,1,3,3,1,2,1,2,3,1 };

std::stack<int> st;

std::vector<Bullet> bulletList;

int flag = 0;

unsigned char* image_data, *image_data1,*image_data2;
int width, height, num_channels,width1,height1,num_channels1,width2,height2,num_channels2;
GLuint texture;

unsigned char* images_data[25];
int widths[25];
int heights[25];
int nums[25];


short sDirection = MIDDLE;
int bullet = 3;
int shoot = 0; 

float colX, colY;
int dc = 0;

void initGrid(int x, int y) {
	bullet = 3;
	shoot = 0;
	gridX = x;
	gridY = y;

	skyLX = 0;
	skyLY = 50;
	skyMX = 120;
	skyMY = 120;

	grassLX = 0;
	grassLY = 0;
	grassMX = 15;
	grassMY = 70;

	roadLX = 15;
	roadLY = 0;
	roadMX = 45;
	roadMY = 70;

	Tree1.change(10, 20);
	Tree2.change(5, 60);
	Tree3.change(110, 20);
	Tree4.change(110, 60);

	initMarking();
	initObstacle();
	car.change(23, 25);

	
	image_data = stbi_load("car3.png", &width, &height, &num_channels, 0);
	if (!image_data) {
		printf("Error loading car image!\n");
		return; 
	}
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	image_data1 = stbi_load("obstacle2.png", &width1, &height1, &num_channels1, 0);
	if (!image_data1) {
		printf("Error loading car image!\n");
		return; 
	}

	image_data2 = stbi_load("bullet.png", &width2, &height2, &num_channels2, 0);
	if (!image_data2) {
		printf("Error loading car image!\n");
		return;
	}

	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
		int index = (i) + j*5;
		if (index == 0) {
			continue;
		}
		std::string base_path = "images/";
		std::stringstream ss;
		ss << base_path << i <<j<< ".png";
		std::string file_path = ss.str();
		
		images_data[index] = stbi_load(file_path.c_str(), &widths[index], &heights[index], &nums[index], 0);
		if (!images_data[index]) {
			printf("Error loading car image! File path: %s\n", file_path.c_str());
			return; 
		}
	}
}
	leftActive.clear();
	rightActive.clear();
	middleActive.clear();
	sDirection = MIDDLE;
	
}

void initMarking() {
	float x = 27.5;
	float j = 83.5;
	for (int i = 0; i < 8; i++) {
		m1[i].change(x, j);
		j -= 10;
	}

	x = 57.5;
	j = 83.5;
	for (int i = 0; i < 8; i++) {
		m2[i].change(x, j);
		j -= 10;
	}
	x = 87.5;
	j = 83.5;
	for (int i = 0; i < 8; i++) {
		m3[i].change(x, j);
		j -= 10;
	}

}

void initObstacle() {
	std::stack<int> st2;
	st = st2;
	leftActive.clear();
	rightActive.clear();
	middleActive.clear();
	for (auto it : obslist1) {
		st.push(it);
	}
	std::cout << st.size();

}



void drawTree(Tree obj) {
	float x = obj.getX();
	float y = obj.getY();

	glColor3f(0.6, 0.3, 0.1);
	glRectd(x, y, x + 1, y + 4);

	float midPoint = (x - 1 + x + 2) / 2;

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 1, y + 4);
	glVertex2f(midPoint, y + 7.464);
	glVertex2f(x + 2, y + 4);
	glEnd();

	
}


void drawGrass() {
	glColor3f(0.486, 0.988, 0.0); 
	glRectd(grassLX, grassLY, grassMX, grassMY);
	glRectd(grassLX+105, grassLY, grassMX+105, grassMY);



	drawTree(Tree1);
	drawTree(Tree2);
	drawTree(Tree3);
	drawTree(Tree4);

	Tree1.changeY();
	Tree2.changeY();
	Tree3.changeY();
	Tree4.changeY();

	
}

void drawRoad() {
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(roadLX+30, roadLY); 
	glVertex2f(roadLX+30, roadMY); 
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(roadLX + 60, roadLY); 
	glVertex2f(roadLX + 60, roadMY); 
	glEnd();

	
}

void drawMarking() {
	for (int i = 0; i < 8; i++) {
		int x1 = m1[i].getX();
		
		int x2 = m2[i].getX();
		int x3 = m3[i].getX();

		int y1 = m1[i].getY();
		int y2 = m2[i].getY();
		int y3 = m3[i].getY();

		glColor3f(1.0, 1.0, 1.0);
		glRectd(x1, y1,x1+2.5,y1+6.5);
		glRectd(x2, y2, x2 + 2.5, y2 + 6.5);
		glRectd(x3, y3, x3 + 2.5, y3 + 6.5);

		m1[i].changeY();
		m2[i].changeY();
		m3[i].changeY();

	}
}

void drawCar() {

	score++;
		int posX = car.getX();
		int posY = car.getY();
		if (sDirection == RIGHT) {
		
			if (posX == 53) {
				sDirection = MIDDLE;
			}
			else if (posX == 83) {
				sDirection = RIGHTSTOP;
			}
			car.steerRight();
		}
		else if (sDirection == LEFT) {
		
			if (posX == 53) {
				sDirection = MIDDLE;
			}
			else if (posX == 23) {
				sDirection = LEFTSTOP;
			}
			car.steerLeft();
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		glEnable(GL_TEXTURE_2D);

	
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(posX, posY);
		glTexCoord2f(1, 0); glVertex2f(posX + 10, posY); 
		glTexCoord2f(1, 1); glVertex2f(posX + 10, posY - 10); 
		glTexCoord2f(0, 1); glVertex2f(posX, posY - 10);
		glEnd();
	 
	
		glDisable(GL_TEXTURE_2D);
	}

void drawObstacle() {
	
	if (!(right.empty())) {
		Obstacle obsr = right.front();
		right.pop();
		rightActive.push_back(obsr);
		
		
	}
	if (!(left.empty())) {
		Obstacle obsl = left.front();
		left.pop();
		leftActive.push_back(obsl);
			
	}
	if (!(middle.empty())) {
		Obstacle obsl = middle.front();
		middle.pop();
		middleActive.push_back(obsl);
			
	}

	if (!st.empty() && flag == 0) {
		if (st.top() == 1) {
			left.push(Obstacle(15, 80));
		}
		else if (st.top() == 2) {
			middle.push(Obstacle(45, 80));
		}
		else {
			right.push(Obstacle(75, 80));
		}
		st.pop();
	}
	flag = (flag + 1) % 30;

	if (leftActive.size() == rightActive.size() == middleActive.size() == 0 && st.empty()) {
		finished = 1;
	}

	

	for (int i = 0; i <rightActive.size(); i++) {
		float posX = rightActive[i].getX();
		float posY = rightActive[i].getY();
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data1);
		glEnable(GL_TEXTURE_2D);
		float aspectRatio = (float)width1 / (float)height1;
		float tex_width = 1.0f;
		float tex_height = 1.0f / aspectRatio;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(posX + 10, posY);
		glTexCoord2f(1, 0); glVertex2f(posX + 15, posY);
		glTexCoord2f(1, 1); glVertex2f(posX + 15, posY - 12);
		glTexCoord2f(0, 1); glVertex2f(posX + 10, posY - 12);
		glEnd();


		glDisable(GL_TEXTURE_2D);

		rightActive[i].changeY();
		if (posY < 0) {

			std::vector<Obstacle>::iterator it = rightActive.begin() + i;
			rightActive.erase(it);
		}
		

	}
	
	for (int i = 0; i < leftActive.size(); i++) {
		float posX = leftActive[i].getX();
		float posY = leftActive[i].getY();
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data1);
		glEnable(GL_TEXTURE_2D);
		float aspectRatio = (float)width1 / (float)height1;
		float tex_width = 1.0f;
		float tex_height = 1.0f / aspectRatio;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(posX + 10, posY);
		glTexCoord2f(1, 0); glVertex2f(posX + 15, posY);
		glTexCoord2f(1, 1); glVertex2f(posX + 15, posY - 12);
		glTexCoord2f(0, 1); glVertex2f(posX + 10, posY - 12);
		glEnd();


		glDisable(GL_TEXTURE_2D);

		leftActive[i].changeY();
		if (posY < 0) {
			std::vector<Obstacle>::iterator it = leftActive.begin() + i;
			leftActive.erase(it);
		}
	}

	for (int i = 0; i < middleActive.size(); i++) {
		float posX = middleActive[i].getX();
		float posY = middleActive[i].getY();
		

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data1);
		glEnable(GL_TEXTURE_2D);
		float aspectRatio = (float)width1 / (float)height1;
		float tex_width = 1.0f;
		float tex_height = 1.0f / aspectRatio;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(posX+10, posY);
		glTexCoord2f(1, 0); glVertex2f(posX + 15, posY);
		glTexCoord2f(1, 1); glVertex2f(posX + 15, posY - 12);
		glTexCoord2f(0, 1); glVertex2f(posX+10, posY - 12);
		glEnd();


		glDisable(GL_TEXTURE_2D);



		middleActive[i].changeY();
		if (posY < 0) {
			std::vector<Obstacle>::iterator it = middleActive.begin() + i;
			middleActive.erase(it);

		}
	}
}
void initBullet() {
	int posX = car.getX();
	int posY = car.getY() + 12;

	Bullet obj(posX+1, posY);
	bulletList.push_back(obj);
	shoot = 0;
}

void drawBullet() {

	for (int i = 0; i < bulletList.size(); i++) {
		float y = bulletList[i].getY();
		float x = bulletList[i].getX();
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data2);
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x, y);
		glTexCoord2f(1, 0); glVertex2f(x + 5,y);
		glTexCoord2f(1, 1); glVertex2f(x + 5, y- 12);
		glTexCoord2f(0, 1); glVertex2f(x, y - 12);
		glEnd();


		glDisable(GL_TEXTURE_2D);

		
		bulletList[i].changeY();

		if (y+1 > 80) {
			std::vector<Bullet>::iterator it = bulletList.begin() + i;
			bulletList.erase(it);
			
		}
		for (int j = 0; j < leftActive.size(); j++) {
			float obsTop = leftActive[j].getY();
			float obsBottom = leftActive[j].getY() - 10;
			float obsLeft = leftActive[j].getX() + 10;
			float obsRight = leftActive[j].getX() + 15;

			float bulletLeft = x;
			float bulletRight = x + 5;
			float bulletTop = y;
			float bulletBottom = y - 12;

			// Check for collision
			if (bulletRight - 1 >= obsLeft && bulletLeft + 1 <= obsRight &&
				bulletTop - 1 >= obsBottom && bulletBottom + 1 <= obsTop) {

				colX = x;
				colY = y;
				dc = 1;

				std::vector<Obstacle>::iterator it1 = leftActive.begin() + j;
				leftActive.erase(it1);
				std::vector<Bullet>::iterator it2 = bulletList.begin() + i;
				bulletList.erase(it2);
			}
		}

		for (int j = 0; j < rightActive.size(); j++) {
			float obsTop = rightActive[j].getY();
			float obsBottom = rightActive[j].getY() - 10;
			float obsLeft = rightActive[j].getX() + 10;
			float obsRight = rightActive[j].getX() + 15;

			float bulletLeft = x;
			float bulletRight = x + 5;
			float bulletTop = y;
			float bulletBottom = y - 12;

			if (bulletRight - 1 >= obsLeft && bulletLeft + 1 <= obsRight &&
				bulletTop - 1 >= obsBottom && bulletBottom + 1 <= obsTop) {
				std::vector<Obstacle>::iterator it1 = rightActive.begin() + j;
				rightActive.erase(it1);
				std::vector<Bullet>::iterator it2 = bulletList.begin() + i;
				bulletList.erase(it2);
			}
		}

		for (int j = 0; j < middleActive.size(); j++) {
			float obsTop = middleActive[j].getY();
			float obsBottom = middleActive[j].getY() - 10;
			float obsLeft = middleActive[j].getX() + 10;
			float obsRight = middleActive[j].getX() + 15;

			float bulletLeft = x;
			float bulletRight = x + 5;
			float bulletTop = y;
			float bulletBottom = y - 12;

			if (bulletRight - 1 >= obsLeft && bulletLeft + 1 <= obsRight &&
				bulletTop - 1 >= obsBottom && bulletBottom + 1 <= obsTop) {
				std::vector<Obstacle>::iterator it1 = middleActive.begin() + j;
				middleActive.erase(it1);
				std::vector<Bullet>::iterator it2 = bulletList.begin() + i;
				bulletList.erase(it2);
			}
		}
	
	}
}

void drawExplosion() {
	static GLuint textureExplosion;

	int drawFlag = 0;
	if (!textureExplosion) {
		glGenTextures(1, &textureExplosion);
		glBindTexture(GL_TEXTURE_2D, textureExplosion);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	for (int i = 1; i < 24; i++) {
		glBindTexture(GL_TEXTURE_2D, textureExplosion);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widths[i], heights[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, images_data[i]);

		if (drawFlag == 0) { 
			for (int j = 0; j < 500; j++) {
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0, 1.0, 1.0);

				glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex2f(colX - 2, colY);
				glTexCoord2f(1, 0); glVertex2f(colX + 10, colY);
				glTexCoord2f(1, 1); glVertex2f(colX + 10, colY - 12);
				glTexCoord2f(0, 1); glVertex2f(colX - 2, colY - 12);
				glEnd();

				glDisable(GL_TEXTURE_2D);
			}
			drawFlag = 1;
		}
		else {
			drawFlag = (drawFlag + 1) % 5; 
		}
	}
	dc = 0;
}

void collisionDetection() {
	float carTop = car.getY();
	float carBottom = car.getY() - 10;
	float carLeft = car.getX();
	float carRight = car.getX() + 5;

	for (int i = 0; i < leftActive.size(); i++) {
		float obsTop = leftActive[i].getY() ;
		float obsBottom = leftActive[i].getY()-10;
		float obsLeft = leftActive[i].getX()+10;
		float obsRight = leftActive[i].getX() + 15;

		if (carRight-1 >= obsLeft && carLeft+1 <= obsRight &&
			carTop-1 >= obsBottom && carBottom+1 <= obsTop) {
			crashed = 1;
			std::cout << "Collision detected with obstacle " << i << " on the left" << std::endl;
		}
	}

	for (int i = 0; i < rightActive.size(); i++) {
		float obsTop = rightActive[i].getY();
		float obsBottom = rightActive[i].getY()-10;
		float obsLeft = rightActive[i].getX()+10;
		float obsRight = rightActive[i].getX() + 15;

		if (carRight-1 >= obsLeft && carLeft+1 <= obsRight &&
			carTop-1 >= obsBottom && carBottom+1 <= obsTop) {
			crashed = 1;
			std::cout << "Collision detected with obstacle " << i << " on the right" << std::endl;
		}
	}

	for (int i = 0; i < middleActive.size(); i++) {
		float obsTop = middleActive[i].getY() ;
		float obsBottom = middleActive[i].getY()-10;
		float obsLeft = middleActive[i].getX()+10;
		float obsRight = middleActive[i].getX()+15 ;

		if (carRight-1 >= obsLeft && carLeft+1 <= obsRight &&
			carTop-1 >= obsBottom && carBottom+1 <= obsTop) {

			crashed = 1;
			std::cout << "Collision detected with obstacle " << score << " in the middle" << std::endl;
			
		}
	}


}

void showScore() {
	char scoreMessage[30] = "Your score is: ";

	char scoreStr[10]; 
	sprintf_s(scoreStr, "%d", score); 

	strcat_s(scoreMessage, scoreStr);

	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2f(100, 60);

	for (int i = 0; scoreMessage[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreMessage[i]);
	}
}


void finalScore() {
	char scoreMessage[30] = "Your score is: ";

	char scoreStr[10];
	sprintf_s(scoreStr, "%d", score); 

	strcat_s(scoreMessage, scoreStr);

	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2f(50, 55);

	for (int i = 0; scoreMessage[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreMessage[i]);
	}
}

void finalScore2() {
	char scoreMessage[30] = "Your score is: ";

	char scoreStr[10]; 
	sprintf_s(scoreStr, "%d", score); 

	strcat_s(scoreMessage, scoreStr);

	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2f(50, 45);


	for (int i = 0; scoreMessage[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreMessage[i]);
	}
}

