#include <gl/glut.h>
#include "game.h"
#include "tree.h"
#include "marking.h"
#include "menu.h"
#include<iostream>

#define COLUMNS 120
#define ROWS 70
extern short FPS;

extern short sDirection;
extern short gamePaused;
extern short gameMain;
extern short crashed;
extern int score;
extern short finished;
extern int bullet;
extern int shoot;
extern int dc;


void timer_callback(int);
void displayCallback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int);
void keyboard_callback2(unsigned char, int, int);

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(COLUMNS, ROWS);
    score = 0;

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowSize(1536, 864);
    glutCreateWindow("Obstacle Driving");
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(keyboard_callback2);
    init();
    glutMainLoop();
    return 0;
}
int index = 0;
void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (gamePaused == 0 && gameMain == 0 && crashed == 0 && finished ==0) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawGrass();

        drawRoad();
        drawMarking();
        drawCar();
        drawObstacle();
        if (shoot == 1) {
            initBullet();
        }
        drawBullet();
        if (dc == 1) {
            drawExplosion();
        }
        collisionDetection();
        showScore(); 
    }
    else if (gameMain == 1) {

      
        glColor3f(1, 1, 1);
        drawMain();
        showScore();
    }
    else if (crashed == 1) {
        glColor3f(1, 1, 1);
        drawCrashed();
        finalScore();
    }
    else if (finished == 1) {
        glColor3f(1, 1, 1);
        drawFinished();
        finalScore2();
    }
    else {
        
        glColor3f(1,1,1);
        drawPause();
        
    }
    glutSwapBuffers();
    
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}
void keyboard_callback(int key, int, int) {
    
    std::cout << key << std::endl;
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (sDirection != LEFTSTOP)
            sDirection = LEFT;
        break;
    case GLUT_KEY_RIGHT:
        if (gameMain == 1) {
            gameMain = 0;

        }
        if (sDirection != RIGHTSTOP)
            sDirection = RIGHT;
        break;
    
    }
    
}

void keyboard_callback2(unsigned char key, int, int) {
    std::cout << key << std::endl;
    switch (key)
    {

    case 13:
        if (gameMain == 1) {
            gameMain = 0;

        }
        else if (gamePaused == 1) {
            gamePaused = 0;
        }
        else if (crashed == 1) {
            crashed = 0;
            score = 0;
            initGrid(COLUMNS, ROWS);
        }
        else if(finished == 1) {
            finished = 0;
            score = 0;
            initGrid(COLUMNS, ROWS);
        }
        break;
    case 27:
        if (gameMain == 1) {
            exit(0);
            break;

        }
        else if (gameMain == 0 && gamePaused == 0) {
            gamePaused = 1;

        }
        break;

    case 'q':
        if (gamePaused == 1) {
            gamePaused = 0;
            gameMain = 1;
            initGrid(COLUMNS,ROWS);
        }
        else if (crashed == 1) {
            crashed = 0;
            gameMain = 1;
            initGrid(COLUMNS, ROWS);
            score = 0;
        }
        else if(finished == 1) {
            gameMain = 1;
            finished = 0;
            score = 0;
            initGrid(COLUMNS, ROWS);
      
        }
        break;

    case 32:
        if (bullet  >0) {
            bullet--;
            shoot = 1;
        }
        
    }

}