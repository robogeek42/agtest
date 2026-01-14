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
    TAB(0,1); printf("This is APP1\n");
    int num = input_int(0,2,"Enter a number");
    printf("\nYour number is %d\n", num);

    clear_keys();
    printf("\nPress any key\n");
    wait_for_any_key();

#ifdef AGONDEV
	kbuf_deinit();
#endif
    return 0;
}

