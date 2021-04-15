#include "contiki.h"
#include "lib/random.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
/**************************************************************************************************
 * PRIVATE TYPES
 *************************************************************************************************/
static process_event_t send_hex;
static process_event_t call_sensor;
static process_event_t estado_sensor;
static process_event_t estado_luz;
static process_event_t call_luz;
/**************************************************************************************************
 * PRIVATE DATA
 *************************************************************************************************/
static int quantidade_callback = 0;
static int sensor_ligado = 0;
static int sensor_desligado = 1;
static int luz_ligada = 2;
static int luz_apagada = 3;
static int arr_sensores[4] = {0};
static int quantidade_luz_apagada = 0;
static int quantidade_sensor_desligado = 0;

/**************************************************************************************************
 * PRIVATE PROTOTYPES
 *************************************************************************************************/
static void event_callback(void *ptr){
    //Caso em que o usuário tenta desligar uma TV antes de ligá-la
    printf("\n\n a cada 5 segundos houve:\n%d numero de sensores ligados:.\n%d numero de sensores desligados.\n%d numero de luz ligada.\n%d numero de luz desligada.\n\n",
        arr_sensores[sensor_ligado],arr_sensores[sensor_desligado],arr_sensores[luz_ligada],arr_sensores[luz_apagada]);

    for (int i = 0; i < 4; i++)
    {
        arr_sensores[i] = 0;
    }
    
    ctimer_reset((struct ctimer*) ptr);
}

static void sensor_callback(void *ptr){
    //Caso em que o usuário tenta desligar uma TV antes de ligá-la
    if (quantidade_luz_apagada >= 2)
    {
        printf("acao indevida");
    }
    
    ctimer_reset((struct ctimer*) ptr);
}

static void luz_callback(void *ptr){
    //Caso em que o usuário tenta desligar uma TV antes de ligá-la
    if (quantidade_sensor_desligado >= 2)
    {
        printf("acao indevida");
    }
    
    ctimer_reset((struct ctimer*) ptr);
}

/**************************************/

PROCESS(serial_simulator, "Serial Simulator");
PROCESS(main_process, "Main Process");
PROCESS(sensores_process, "Sensor Process");
PROCESS(luz_process, "Luz Process");

AUTOSTART_PROCESSES(&serial_simulator, &main_process,&sensores_process,&luz_process);

PROCESS_THREAD(serial_simulator,ev,data)
{
  static uint8_t rand; 
  static struct etimer timer;
  int length = 2;
  int i;
  char hex[] = "0123456789ABCDEF";
  static char buffer[2];
  send_hex = process_alloc_event();
  PROCESS_BEGIN();
  etimer_set(&timer, CLOCK_SECOND * 1);
  while(1) {
    for(i=0; i<length; i++) 
    {
      rand = (random_rand() % 16);
      buffer[i] = hex[rand];
      
    } 
    printf("Sending 0x%s to main process...\n", buffer);
    process_post(&main_process,send_hex,&buffer);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }
  PROCESS_END();
}

PROCESS_THREAD(main_process,ev,data)
{
  int stats;
  
  call_sensor = process_alloc_event();
  call_luz = process_alloc_event();
  PROCESS_BEGIN();
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev = send_hex);
    char *buffer = data;
    printf("Received something from serial port...\n");
    if(isdigit(buffer[0])){
      stats=1;
      process_post(&sensores_process,call_sensor,buffer);
    }
    else if(!isdigit(buffer[0])){
      stats=2;
      process_post(&luz_process,call_luz,buffer);
    }
    else {
      continue;
    }
    
    if(stats==1) {
      PROCESS_WAIT_EVENT_UNTIL(ev = estado_sensor);
      uint8_t tvcode = ((intptr_t)data);
      if(tvcode==1){
        arr_sensores[sensor_ligado]++;
        printf("--------------->O sensor esta ligado\n");
      }
      if(tvcode==0) {
        arr_sensores[sensor_desligado]++;
        if (quantidade_callback == 99){
            memset(arr_sensores, -1, sizeof(arr_sensores));
            quantidade_callback = 0;
        }
        
        printf("--------------->o sensor esta desligado.\n");
      }
    }
    else if(stats==2) {
      PROCESS_WAIT_EVENT_UNTIL(ev = estado_luz);
      uint8_t dvdcode = ((intptr_t)data);
      if(dvdcode==1){
        printf("--------------->a luz esta ligada.\n");
      }
      if(dvdcode==0){
        printf("--------------->a luz esta apagada.\n");
      }
    }
    else {
      continue;
    }
    
  }
  PROCESS_END();
}

PROCESS_THREAD(sensores_process,ev,data)
{
  static struct ctimer ct;
  static struct ctimer ct_t;
  static bool statusTv = false; 
  static uint8_t code;
  estado_sensor = process_alloc_event();
  PROCESS_BEGIN();

  ctimer_set(&ct, 10 * CLOCK_SECOND, event_callback, &ct);
  ctimer_set(&ct_t, 1 * CLOCK_SECOND, luz_callback, &ct_t);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev = call_sensor);
    char *buffer = data;
    printf("Sensor recebido: %s\n",buffer);
    if(statusTv){
      statusTv = false;
      code = 0;
      arr_sensores[sensor_desligado]++;
      quantidade_sensor_desligado++;
      process_post(&main_process,estado_sensor,&code);
    }
    else {
      statusTv = true;
      code = 1;
      arr_sensores[sensor_ligado]++;
      quantidade_sensor_desligado = 0;
      process_post(&main_process,estado_sensor,&code);
    }
  }
  PROCESS_END();
}

PROCESS_THREAD(luz_process,ev,data)
{
  static struct ctimer ct_d;
  static bool statusDvd = false; 
  static uint8_t dcode;
  estado_luz = process_alloc_event();

  ctimer_set(&ct_d, 1 * CLOCK_SECOND, sensor_callback, &ct_d);

  PROCESS_BEGIN();
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev = call_luz);
    char *buffer = data;
    printf("Luz recebida: %s\n",buffer);
    if(statusDvd){
      statusDvd = false;
      dcode = 0;
      arr_sensores[luz_apagada]++;
      quantidade_luz_apagada++;
      process_post(&main_process,estado_luz,&dcode);
    }
    else {
      statusDvd = true;
      dcode = 1;
      arr_sensores[luz_ligada]++;
      quantidade_luz_apagada = 0;
      process_post(&main_process,estado_luz,&dcode);
    }
  }
  PROCESS_END();
}