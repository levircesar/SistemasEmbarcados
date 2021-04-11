#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


PROCESS(main_process, "Principal");
PROCESS(process_1, "Processo 1");
PROCESS(process_2, "Processo 2");

static process_event_t send_buffer_to_p1;
static process_event_t send_buffer_to_p2;
static process_event_t send_buffer_to_main; 


AUTOSTART_PROCESSES(&main_process,&process_1,&process_2);

PROCESS_THREAD(main_process, ev, data){
	
	int i = 0;
	char buffer[10];
	static char static_buffer[10];

	PROCESS_BEGIN(); 
	
 	send_buffer_to_p1 = process_alloc_event();
 	send_buffer_to_p2 = process_alloc_event();


	while(1){
		
		printf("escreva uma palavra \n");
		printf("Ciclo numero %d \r\n", i);
		if(scanf("%s",buffer)){
			printf("buffer recebido: ");
			fputs(buffer,stdout);
			printf("\n");
		}

		for(i = 0; i< 10; i ++){
			static_buffer[i] = buffer[i];
		}

		if( static_buffer[0] == 'a'){
			process_post(&process_1 , send_buffer_to_p1,&static_buffer);
			printf("buffer enviado para o primeiro \n");
		}else{
			process_post(&process_2 , send_buffer_to_p2,&static_buffer);
			printf("buffer enviado para o segundo \n");
		}
	
	
		PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_main);
		printf("um processo secundario enviou um buffer de volta \n");
		char *ponteiro = data;
		fputs(ponteiro,stdout);
		printf("\n");
	}

	PROCESS_END();

}

PROCESS_THREAD(process_1, ev, data)
{
    static char secondary_buffer[10];
	int i = 0;
	
    PROCESS_BEGIN(); 
	send_buffer_to_main = process_alloc_event();
    while (1)
    {
        
        PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_p1);
        printf("processo 1\n");
		char *ponteiro = data;
		printf("ponteiro no processo 1\n");
		fputs(data,stdout);
		printf("\n");
        
		for(i = 0; i< 10; i ++){
			secondary_buffer[i] = ponteiro[i];
		}

		secondary_buffer[0] = 0x41;
		printf("buffer do processo 1: ");
		fputs(secondary_buffer,stdout);
		printf("\n");

		process_post(&main_process , send_buffer_to_main,&secondary_buffer);

    }
    PROCESS_END();
}


PROCESS_THREAD(process_2, ev, data)
{
    static char secondary_buffer[10];
	int i = 0;
	
    PROCESS_BEGIN(); 
	send_buffer_to_main = process_alloc_event();
    while (1)
    {
        
        PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_p2);
        printf("processo 2\n");
		char *ponteiro = data;
		printf("ponteiro no processo 2\n");
		fputs(data,stdout);
		printf("\n");
        
		for(i = 0; i< 10; i ++){
			secondary_buffer[i] = ponteiro[i];
		}

		secondary_buffer[0] = 0x41;
		printf("buffer do processo 2: ");
		fputs(secondary_buffer,stdout);
		printf("\n");

		process_post(&main_process , send_buffer_to_main,&secondary_buffer);

    }
    PROCESS_END();
}