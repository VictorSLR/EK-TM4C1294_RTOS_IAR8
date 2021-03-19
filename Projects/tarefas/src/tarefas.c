#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

typedef struct leds_arg {
   int led;
   int tempo;
} leds_arg;

void thread1(void *arg){
  leds_arg* thr_led = (leds_arg*) arg;
  uint8_t state = 0;
  
  while(1){
    state ^= thr_led->led;
    LEDWrite(thr_led->led, state);
    osDelay(thr_led->tempo);
  } // while
} // thread1


void main(void){
  LEDInit(LED2 | LED1 | LED3 | LED4);

  osKernelInitialize();
  
  leds_arg led1, led2, led3, led4;
  
  led1.led = LED1;
  led1.tempo = 200;
  led2.led = LED2;
  led2.tempo = 300;
  led3.led = LED3;
  led3.tempo = 500;
  led4.led = LED4;
  led4.tempo = 700;

  thread1_id = osThreadNew(thread1, &led1, NULL);
  thread2_id = osThreadNew(thread1, &led2, NULL);
  thread3_id = osThreadNew(thread1, &led3, NULL);
  thread4_id = osThreadNew(thread1, &led4, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
