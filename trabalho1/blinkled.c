#include "contiki.h"
#include <stdio.h>
#include <stdint.h>

 
/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
 

/**************************************************************************************************
 * PRIVATE PROTOTYPES
 *************************************************************************************************/
void blinkledfunction(bool);


/**************************************************************************************************
 * PRIVATE DATA
 *************************************************************************************************/
//bool valor = false;

/**************************************************************************************************
 * FUNCTIONS DEFINITIONS
 *************************************************************************************************/
void blinkledfunction(bool gatilho){
	if((gatilho) == true){
     //   valor = false;
		printf("BLINK LEDS ON\r\n");
	}else {
    //    valor = true;
		printf("BLINK LEDS OFF\r\n");
	}
}

//bool get_leds_state(void){
//	return valor;
//}

/**************************************/
PROCESS(blinkled, "UART Led process");

PROCESS_THREAD(blinkled, ev, data)
{
   //static struct etimer timer;	
	
    PROCESS_BEGIN(); 
    while (1)
    {
        // we set the timer from here every time
        // etimer_set(&timer, CLOCK_CONF_SECOND * 4);
        
        // and wait until the vent we receive is the one we're waiting for
       PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
		//blinkledfunction(valor);
        //printf("valor do led = %d\r\n", valor);

    }
    PROCESS_END();
}
