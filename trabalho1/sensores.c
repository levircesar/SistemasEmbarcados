#include "contiki.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
 
 
/**************************************************************************************************
 * PRIVATE PROTOTYPES
 *************************************************************************************************/
static void read_temperature(void);
static void read_humidity(void);
static void read_pressure(void);


/**************************************************************************************************
 * PRIVATE DATA
 *************************************************************************************************/
static float temperature = 0;
static float humidity = 0;
static float pressure = 0;

/**************************************************************************************************
 * FUNCTIONS DEFINITIONS
 *************************************************************************************************/

static float random_value(float min, float max)
{
 float scale = rand() / (float) RAND_MAX;
 return min + scale * (max - min);
}

static void read_temperature(void)
{
 temperature = random_value(15, 35);
}

static void read_humidity(void)
{
 humidity = random_value(40, 80);
}

static void read_pressure(void)
{
 pressure = random_value(30, 78);
}


float get_read_temperature(void){
    return temperature;
}
float get_read_humidity(void){
    return humidity;
}
float get_read_pressure(void){
    return pressure;
}

/**************************************/
PROCESS(sensores, "Meus sensores");

PROCESS_THREAD(sensores, ev, data)
{
    static struct etimer timer;	
	
    PROCESS_BEGIN(); 
    while (1)
    {
        // we set the timer from here every time
        etimer_set(&timer, CLOCK_CONF_SECOND * 5);
        
        // and wait until the vent we receive is the one we're waiting for
      
        
		read_temperature();
        read_humidity();
        read_pressure();
	//	printf("captando sensores \n");
     PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

    }
    PROCESS_END();
}
