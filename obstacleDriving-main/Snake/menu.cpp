#include "menu.h"
#include<gl/glut.h>
#include<string.h>
#include<string>
#include "stb_image.h"
#include<iostream>


extern short gamePaused;
short gameMain = 1;


#define ROWS 70
#define COLUMNS 120

void drawMain() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Load the PNG image
    int width, height, num_channels;

    unsigned char* image_data = stbi_load("mainmenu3.png", &width, &height, &num_channels, 0);
    if (!image_data) {
        printf("Error loading main menu image!\n");
        return; // Handle error if image fails to load
    }



    // Create a texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (consider adjusting filtering based on your needs)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture data (assuming your image data is in RGB format)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    // Enable texturing for subsequent drawing
    glEnable(GL_TEXTURE_2D);

    // Calculate texture coordinates
    float aspectRatio = (float)width / (float)height;
    float tex_width = 1.0f;
    float tex_height = 1.0f / aspectRatio;

    // Draw a rectangle covering the whole screen with the loaded image as texture
    glBegin(GL_QUADS);
    glTexCoord2f(0, 12); glVertex2f(0, 0); // Bottom-left corner (texture top-left)
    glTexCoord2f(12.7, 12); glVertex2f(screenWidth, 0); // Bottom-right corner (texture top-right)
    glTexCoord2f(12.7, 0); glVertex2f(screenWidth, screenHeight); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(0, screenHeight); // Top-left corner (texture bottom-left)
    glEnd();






    // Disable texture
    glDisable(GL_TEXTURE_2D);

    stbi_image_free(image_data);

}

void drawPause() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Load the PNG image
    int width, height, num_channels;
    unsigned char* image_data = stbi_load("pausemenu3.png", &width, &height, &num_channels, 0);
    if (!image_data) {
        printf("Error loading main menu image!\n");
        return; // Handle error if image fails to load
    }

    // Create a texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (consider adjusting filtering based on your needs)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture data (assuming your image data is in RGB format)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    // Enable texturing for subsequent drawing
    glEnable(GL_TEXTURE_2D);

    // Calculate texture coordinates
    float aspectRatio = (float)width / (float)height;
    float tex_width = 1.0f;
    float tex_height = 1.0f / aspectRatio;

    int x1 = screenWidth / 4;
    int x2 = (3 * screenWidth) / 4;
    int y1 = screenHeight / 4;
    int y2 = (3 * screenHeight) / 4;

    // Draw a rectangle covering the whole screen with the loaded image as texture
    /*=glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(x1, y1); // Bottom-left corner (texture top-left)
    glTexCoord2f(1, 1); glVertex2f(x2, y1); // Bottom-right corner (texture top-right)
    glTexCoord2f(1, 0); glVertex2f(x2, y2); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(x1, y2); // Top-left corner (texture bottom-left)
    glEnd();*/

    glBegin(GL_QUADS);
    glTexCoord2f(0, 12); glVertex2f(0, 0); // Bottom-left corner (texture top-left)
    glTexCoord2f(12.7, 12); glVertex2f(screenWidth, 0); // Bottom-right corner (texture top-right)
    glTexCoord2f(12.7, 0); glVertex2f(screenWidth, screenHeight); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(0, screenHeight); // Top-left corner (texture bottom-left)
    glEnd();





    // Disable texture
    glDisable(GL_TEXTURE_2D);

    stbi_image_free(image_data);

   
}

void drawCrashed() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Load the PNG image
    int width, height, num_channels;
    unsigned char* image_data = stbi_load("crashed.png", &width, &height, &num_channels, 0);
    if (!image_data) {
        printf("Error loading main menu image!\n");
        return; // Handle error if image fails to load
    }

    // Create a texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (consider adjusting filtering based on your needs)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture data (assuming your image data is in RGB format)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    // Enable texturing for subsequent drawing
    glEnable(GL_TEXTURE_2D);

    // Calculate texture coordinates
    float aspectRatio = (float)width / (float)height;
    float tex_width = 1.0f;
    float tex_height = 1.0f / aspectRatio;

    int x1 = screenWidth / 4;
    int x2 = (3 * screenWidth) / 4;
    int y1 = screenHeight / 4;
    int y2 = (3 * screenHeight) / 4;

    // Draw a rectangle covering the whole screen with the loaded image as texture
    /*=glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(x1, y1); // Bottom-left corner (texture top-left)
    glTexCoord2f(1, 1); glVertex2f(x2, y1); // Bottom-right corner (texture top-right)
    glTexCoord2f(1, 0); glVertex2f(x2, y2); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(x1, y2); // Top-left corner (texture bottom-left)
    glEnd();*/

    glBegin(GL_QUADS);
    glTexCoord2f(0, 12); glVertex2f(0, 0); // Bottom-left corner (texture top-left)
    glTexCoord2f(12.7, 12); glVertex2f(screenWidth, 0); // Bottom-right corner (texture top-right)
    glTexCoord2f(12.7, 0); glVertex2f(screenWidth, screenHeight); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(0, screenHeight); // Top-left corner (texture bottom-left)
    glEnd();





    // Disable texture
    glDisable(GL_TEXTURE_2D);


}

void drawFinished() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Load the PNG image
    int width, height, num_channels;
    unsigned char* image_data = stbi_load("finished.png", &width, &height, &num_channels, 0);
    if (!image_data) {
        printf("Error loading main menu image!\n");
        return; // Handle error if image fails to load
    }

    // Create a texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (consider adjusting filtering based on your needs)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load texture data (assuming your image data is in RGB format)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    // Enable texturing for subsequent drawing
    glEnable(GL_TEXTURE_2D);

    // Calculate texture coordinates
    float aspectRatio = (float)width / (float)height;
    float tex_width = 1.0f;
    float tex_height = 1.0f / aspectRatio;

    int x1 = screenWidth / 4;
    int x2 = (3 * screenWidth) / 4;
    int y1 = screenHeight / 4;
    int y2 = (3 * screenHeight) / 4;

    // Draw a rectangle covering the whole screen with the loaded image as texture
    /*=glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(x1, y1); // Bottom-left corner (texture top-left)
    glTexCoord2f(1, 1); glVertex2f(x2, y1); // Bottom-right corner (texture top-right)
    glTexCoord2f(1, 0); glVertex2f(x2, y2); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(x1, y2); // Top-left corner (texture bottom-left)
    glEnd();*/

    glBegin(GL_QUADS);
    glTexCoord2f(0, 12); glVertex2f(0, 0); // Bottom-left corner (texture top-left)
    glTexCoord2f(12.7, 12); glVertex2f(screenWidth, 0); // Bottom-right corner (texture top-right)
    glTexCoord2f(12.7, 0); glVertex2f(screenWidth, screenHeight); // Top-right corner (texture bottom-right)
    glTexCoord2f(0, 0); glVertex2f(0, screenHeight); // Top-left corner (texture bottom-left)
    glEnd();





    // Disable texture
    glDisable(GL_TEXTURE_2D);
    stbi_image_free(image_data);

}
