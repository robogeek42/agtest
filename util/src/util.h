/*
  vim:ts=4
  vim:sw=4
*/
#ifndef _UTIL_H
#define _UTIL_H

#ifdef AGONDEV
#include "agon/vdp.h"
#include "agon/mos.h"
#include "agon/keyboard.h"
#else
#include "agon/vdp_vdu.h"
#include "agon/vdp_key.h"
#include "mos_api.h"
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define COL(C) vdp_set_text_colour(C)
#define TAB(X,Y) vdp_cursor_tab(X,Y)


#ifdef AGONDEV
#else
extern uint8_t key_pressed_ascii;
extern uint8_t key_pressed_mods;
extern uint8_t key_pressed_code;
void key_event_handler( KEY_EVENT key_event );
#endif
void wait_clock( clock_t ticks );

void draw_box(int x,int y, int w, int h, int col);
void draw_filled_box(int x,int y, int w, int h, int col, int bgcol);

int input_int(int x, int y, char *msg);

// clear keyboard buffer
void clear_keys();
// return after specific key is pressed
uint8_t wait_for_key(uint8_t key);
// return after key is released
uint8_t wait_for_any_key();
// return after key-down event
uint8_t wait_for_any_key_press();

void delay(int timeout);


#endif
