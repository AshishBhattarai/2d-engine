#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

//methods
void createDisplay(int w, int h, const char* title);
bool shouldCloseWindow();
void startLoop();
int getDelta();
void endLoop();
void displayCleanUp();

#endif