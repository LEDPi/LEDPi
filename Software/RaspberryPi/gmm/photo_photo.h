#ifndef _PHOTO_PHOTO_H_
#define _PHOTO_PHOTO_H_

///////////////////////////////////////////////////////////////////////////////
// FILE: photo_photo
// DESC: draws a photo
///////////////////////////////////////////////////////////////////////////////

#include "mux/mux_drawing.h"
#include "mux/draw_buffer_t.h"

#define DRAW_VAL(RED, GREEN, BLUE) { (RED), (GREEN), (BLUE) }

#define PHOTO_VERSION 0x0001

extern draw_buffer_t photo_pi;
extern draw_buffer_t Linux;
extern draw_buffer_t Android_1;
extern draw_buffer_t Android_2;
extern draw_buffer_t Smiley;
 
#endif // _PHOTO_PHOTO_H_
