#include "contiki.h"
#include <stdio.h>
#include <stdint.h>
#include "blinkled.h"

/**************************************************************************************************
 * PRIVATE DEFINES
 *************************************************************************************************/

#define BUFFER_SIZE           			6  


/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
 static uint8_t buffer_c [BUFFER_SIZE];
 static uint8_t i_buffer_c = 0;

/**************************************************************************************************
 * PRIVATE PROTOTYPES
 *************************************************************************************************/
static void blinkledfunction(void);
static void ctimer_event_callback(void *ptr);
static int buffer_circular(uint8_t byte);


/**************************************************************************************************
 * PRIVATE DATA
 *************************************************************************************************/
static uint8_t leds_state = 0;
//static char data_char = 'A';

/**************************************************************************************************
 * FUNCTIONS DEFINITIONS
 *************************************************************************************************/
static void ctimer_event_callback(void *ptr){
	printf("CALLBACK Values: %s.\r\n", buffer_c);
	//check_update_image();
	ctimer_reset((struct ctimer*) ptr);
}

static int buffer_circular(uint8_t byte){
	buffer_c[i_buffer_c] = byte;
	i_buffer_c++;
	if(i_buffer_c > BUFFER_SIZE){
		i_buffer_c = 0;
	}
	return 0;
}
 
static void blinkledfunction(void){

	if((leds_state%2) == 0){
		printf("BLINK LEDS ON\r\n");
	}else {
		printf("BLINK LEDS OFF\r\n");
	}
	leds_state++;
}

uint8_t get_leds_state(void){
	return leds_state;
}

/**************************************/
PROCESS(blinkled, "UART Led process");

PROCESS_THREAD(blinkled, ev, data)
{
    //static struct etimer timer;
	static struct ctimer ct;
	
    PROCESS_BEGIN(); 
	
	/*
	* Set a callback function to be started each N=10 seconds
	* */
	printf("Calling my callback's fucntion.\r\n");
    ctimer_set(&ct, CLOCK_SECOND * 5, ctimer_event_callback, &ct);
	//etimer_set(&timer, CLOCK_SECOND * 6);
	
    while (1){
        // we set the timer from here every tim
        
        // and wait until the vent we receive is the one we're waiting for
        //PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
        
		PROCESS_WAIT_EVENT_UNTIL(ev == EVENT_RCV_POWER_OFF);
		blinkledfunction();
		printf("FROM BLINKLED leds_state = %d\r\n", leds_state);
		printf("BLINK LEDS VALID_DATA = %d\r\n", *((int*)data));
		char *p_data = data;
		buffer_circular(p_data[0]);
		//data_char++;
		
		/*PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        etimer_reset(&timer);*/
    }
    PROCESS_END();
}
