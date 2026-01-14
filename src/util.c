/*
  vim:ts=4
  vim:sw=4
*/
#include "util.h"

#ifdef AGONDEV
void clear_keys()
{
	struct keyboard_event_t e;
    while (kbuf_poll_event(&e)) {}
}
uint8_t wait_for_key(uint8_t key)
{
	struct keyboard_event_t e;
    do {
		while (!kbuf_poll_event(&e)) {}
	} while (e.vkey != key);
    return key;
}
uint8_t wait_for_any_key()
{
	struct keyboard_event_t e;
    while (!kbuf_poll_event(&e)) {}
    return e.vkey;
}
uint8_t wait_for_any_key_press()
{
	struct keyboard_event_t e;
    while (!kbuf_poll_event(&e)) {}
    return e.vkey;
}
#else
uint8_t key_pressed_ascii;
uint8_t key_pressed_mods;
uint8_t key_pressed_code;
void key_event_handler( KEY_EVENT key_event )
{
	if (key_event.down)
	{	
		key_pressed_ascii = key_event.ascii; 
		key_pressed_mods = key_event.mods; 
		key_pressed_code = key_event.code; 
	} else {
		key_pressed_ascii = 0;
		key_pressed_mods = 0;
		key_pressed_code = 0;
	}
}

void clear_keys()
{
	do 
	{
		vdp_update_key_state();
	} while(key_pressed_code != 0);
}
uint8_t wait_for_key(uint8_t key)
{
	bool exit_loop = false;
	do 
	{
		if ( vdp_check_key_press( key ) )
		{
			exit_loop = true;
			// wait so we don't register this press multiple times
			do {
				vdp_update_key_state();
			} while ( vdp_check_key_press( key ) );
		}
		vdp_update_key_state();
	} while ( !exit_loop );

	return key;
}

// return after key is released
uint8_t wait_for_any_key()
{
	do 
	{
		vdp_update_key_state();
	} while(key_pressed_code == 0);
	int key = key_pressed_code;
	while( vdp_check_key_press(key)) vdp_update_key_state();
	return key;
}
// return after key-down event
uint8_t wait_for_any_key_press()
{
	do 
	{
		vdp_update_key_state();
	} while(key_pressed_code == 0);
	int key = key_pressed_code;
	return key;
}
#endif

void wait_clock( clock_t ticks )
{
	clock_t ticks_now = clock();

	do {
#ifndef AGONDEV
		vdp_update_key_state();
#endif
	} while ( clock() - ticks_now < ticks );
}

void draw_box(int x,int y, int w, int h, int col)
{
#ifdef AGONDEV
    vdp_set_graphics_fg_colour(GCOLMODE_COLOUR, col);
    vdp_rectangle(x,y, x+w,y+h);
#else
	vdp_gcol( 0, col );
	vdp_move_to( x, y );
	vdp_line_to( x, y+h );
	vdp_line_to( x+w, y+h );
	vdp_line_to( x+w, y );
	vdp_line_to( x, y );
#endif
}

void draw_filled_box(int x,int y, int w, int h, int col, int bgcol)
{
#ifdef AGONDEV
    vdp_set_graphics_fg_colour(GCOLMODE_COLOUR, bgcol);
    vdp_filled_rectangle(x,y, x+w,y+h);
    vdp_set_graphics_fg_colour(GCOLMODE_COLOUR, col);
    vdp_rectangle(x,y, x+w,y+h);
#else
	vdp_gcol( 0, bgcol );
	vdp_move_to( x, y );
	vdp_filled_rect( x+w, y+h );
	// border
	if (col != bgcol)
	{
		vdp_gcol( 0, col );
		vdp_move_to( x, y );
		vdp_line_to( x, y+h );
		vdp_line_to( x+w, y+h );
		vdp_line_to( x+w, y );
		vdp_line_to( x, y );
	}
#endif
}

int input_int(int x, int y, char *msg)
{
	int num;
	TAB(x,y);
	printf("%s:",msg);
	scanf("%d",&num);
	return num;
}


void delay(int timeout)
{
	clock_t timeout_ticks = clock()+timeout;
	do 
	{
#ifndef AGONDEV
		vdp_update_key_state();
#endif
	} while( timeout_ticks > clock() );
}

