#include "contiki.h"
#include <stdio.h>
#include <stdint.h>

#include "blinkled.h"

PROCESS(helloworld, "My first process in Contiki-ng");

AUTOSTART_PROCESSES(&helloworld);

PROCESS_THREAD(helloworld, ev, data){
	
	static struct etimer timer;
	
	static uint8_t i = 0;
	
	static char valid_data = 'A';

	PROCESS_BEGIN();
	
	process_start(&blinkled, NULL);

	etimer_set(&timer, CLOCK_SECOND * 5);

	while(1){
		printf("Hello, I am using Contiki-ng %d \r\n", i);
		i++ ;
		
		printf("FROM HELLOWORLD leds_state = %d\r\n", get_leds_state());
		
		
		process_post(&blinkled, EVENT_RCV_POWER_OFF, &valid_data);

		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		etimer_reset(&timer);
	}

	PROCESS_END();

}