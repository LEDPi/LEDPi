#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_ROWS 20
#define NUM_COLUMNS 20
#define NUM_VERTICES NUM_ROWS*NUM_COLUMNS*6
#define NUM_VALUES 24*NUM_ROWS*NUM_COLUMNS
#define WINDOW_TITLE_PREFIX "Software Wall"

bool graphic_run();
void InitializeWindow();

#endif  //_GRAPHIC_H_ 
