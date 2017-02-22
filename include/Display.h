#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

//Creates a display with given width, height & title
void createDisplay(int w, int h, char* title);

//Returns if close flage is set or not
bool shouldCloseWindow();

//Prepare the loop - calc FPS, Delta
void startLoop();

//Get the valude of delta
int getDelta();

//Perform some operation at end of loop
void endLoop();

//check ke press
bool isKeyPressed(int key);

//Destroy the window
void displayCleanUp();

#endif