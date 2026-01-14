/*
  vim:ts=4
  vim:sw=4
*/
#ifdef AGONDEV
#include "agon/vdp.h"
#include "agon/mos.h"
#else
#include "agon/vdp_vdu.h"
#include "agon/vdp_key.h"
#include "mos_api.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(/*int argc, char *argv[]*/)
{
	vdp_vdu_init();
#ifdef AGONDEV
	kbuf_init(16);
#else
	if ( vdp_key_init() == -1 ) return 1;
	vdp_set_key_event_handler( key_event_handler );
#endif

    vdp_cls();

    TAB(0,1); printf("This is APP2\n");


    // White box, 100,100 ->200,200
    vdp_gcol(0,7);
#ifdef AGONDEV
    draw_filled_box(100,100,100,100,7,7);
#else
    vdp_move_to(100,100);
    vdp_filled_rect(200,200);
#endif

    // Red unfilled 100x100 box at 50,300 
    draw_box(50,300,100,100,1);
    // Yellow filled 50x50 box at 100,275 with green outline
    draw_filled_box(100,275,50,50,2,3);

    clear_keys();
    printf("\nPress any key\n");
    wait_for_any_key();

#ifdef AGONDEV
	kbuf_deinit();
#endif
    return 0;
}

