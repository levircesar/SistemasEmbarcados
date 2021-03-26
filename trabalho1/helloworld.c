#include "contiki.h"
#include <stdio.h>
#include <stdint.h>

#include "blinkled.h"
#include "sensores.h"

PROCESS(helloworld, "Ciclo numero");

AUTOSTART_PROCESSES(&helloworld);

PROCESS_THREAD(helloworld, ev, data){
	
	static struct etimer timer;
	 
	static uint8_t i = 0;

	PROCESS_BEGIN(); 
	
	process_start(&blinkled, NULL);
	process_start(&sensores, NULL);

	//etimer_set(&timer, 10);

	while(1){
		
		//PROCESS_WAIT_EVENT();
		etimer_set(&timer, CLOCK_CONF_SECOND * 1);
		printf("Ciclo numero %d \r\n", i);
		i++ ;

		printf("valor da umidade = %.2f\r\n", get_read_humidity());
		printf("valor da pressao = %.2f\r\n", get_read_pressure());
		printf("valor da temperatura = %.2f\r\n", get_read_temperature());
		if(get_read_temperature() > 20 ){
			blinkledfunction(true);
		}else{
			blinkledfunction(false);
		}
		
	
		//printf("valor do led = %d\r\n", valor);

		//PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
		//etimer_reset(&timer);
	}

	PROCESS_END();

}

/*PROCESS_THREAD(blinkleds, ev, data)
{
    static struct etimer timer;
    static uint8_t leds_state = 0;
	
	
    PROCESS_BEGIN(); 
    while (1)
    {
        // we set the timer from here every time
        etimer_set(&timer, CLOCK_CONF_SECOND * 2);
        
        // and wait until the vent we receive is the one we're waiting for
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
        
        // update the LEDs
		if((leds_state%2) == 0){
			printf("BLINK LEDS ON\r\n");
		}else {
			printf("BLINK LEDS OFF\r\n");
		}
		leds_state++;
    }
    PROCESS_END();
}*/
