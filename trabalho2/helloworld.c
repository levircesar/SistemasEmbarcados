#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


PROCESS(principal, "Principal");
PROCESS(primeiro, "Processo 1");
PROCESS(segundo, "Processo 2");

static process_event_t send_buffer_to_primeiro;
static process_event_t send_buffer_to_segundo;
static process_event_t send_buffer_to_principal; 


AUTOSTART_PROCESSES(&principal,&primeiro,&segundo);

PROCESS_THREAD(principal, ev, data){
	
	int i = 0;
	char buffer[10];
	static char static_buffer[10];

	PROCESS_BEGIN(); 
	
 	send_buffer_to_primeiro = process_alloc_event();
 	send_buffer_to_segundo = process_alloc_event();


	while(1){
		
		printf("escreva uma palavra \n");
		if(scanf("%s",buffer)){
			printf("buffer recebido: ");
			fputs(buffer,stdout);
			printf("\n");
		}

		for(i = 0; i< 10; i ++){
			static_buffer[i] = buffer[i];
		}

		if( static_buffer[0] == 'a'){
			process_post(&primeiro , send_buffer_to_primeiro,&static_buffer);
			printf("buffer enviado para o primeiro \n");
		}else{
			process_post(&segundo , send_buffer_to_segundo,&static_buffer);
			printf("buffer enviado para o segundo \n");
		}
	
	
		PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_principal);
		printf("um processo secundario enviou um buffer de volta \n");
		char *ponteiro = data;
		fputs(ponteiro,stdout);
		printf("\n");
	}

	PROCESS_END();

}

PROCESS_THREAD(primeiro, ev, data)
{
    static char secondary_buffer[10];
	int i = 0;
	
    PROCESS_BEGIN(); 
	sacend_buffer_to_principal = process_alloc_event();
    while (1)
    {
        
        PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_primeiro);
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

		process_post(&principal , send_buffer_to_principal,&secondary_buffer);

    }
    PROCESS_END();
}


PROCESS_THREAD(segundo, ev, data)
{
    static char secondary_buffer[10];
	int i = 0;
	
    PROCESS_BEGIN(); 
	send_buffer_to_principal = process_alloc_event();
    while (1)
    {
        
        PROCESS_WAIT_EVENT_UNTIL(ev == send_buffer_to_segundo);
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

		process_post(&principal , send_buffer_to_principal,&secondary_buffer);

    }
    PROCESS_END();
}