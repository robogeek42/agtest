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
    // Because AGONDEV supports the MOS3.0 functions we can, e.g. print ENV Vars:
    char variablename[] = "Sys$Time";
    char *transbuff;
    char *actualbuff;
    int transbufflen = 64;
    int actualbufflen = 64;
   
    // malloc a big buffer - cheating
    // this is done properly by calling mos_gstrans twice and getting the correct size

    transbuff = (char*) calloc(transbufflen, sizeof(char)); 
    actualbuff = (char*) calloc(actualbufflen, sizeof(char)); 

    uint8_t ret = mos_readvarval(variablename, transbuff, &actualbuff, &actualbufflen, NULL);
    if (ret != 0)
    {
        printf("Failed to run mos_readvarval() status: %d\n", ret);
    }
    else
    {
        printf("TIME: %s\n", transbuff);
    }
    free(transbuff);
    free(actualbuff);
#else
    printf("AgDev does not support MOS3.0 calls\n");
#endif

#ifdef AGONDEV
	kbuf_deinit();
#endif
    return 0;
}

