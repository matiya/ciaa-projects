#include "main.h"
#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* * variables globales */
/* * funciones locales */
/* ** changeLedState */
/* void updateLeds() { */
/*   gpioToggle(_led); */
/*   delay(_delay); */
/* } */
/* ** scanTec */
/* void scanTec(){ */
/*   for (gpioMap_t i = TEC1; i < TEC4 + 1; i++){ */
/*     if(!(gpioRead(i))){ */
/*       _delay = delay_list[i - TEC1]; */
/*     } */
/*   } */
/*   return 0; */
/* } */
/* ** readUart */
/* void readUart() { */
/*   uint8_t received; */
/*   uartReadByte(UART_USB, &received); */
    
/*   switch (received) { */
/*   case 'a': { */
/*     _led = LEDB; */
/*     break; */
/*   } */
/*   case '1': { */
/*     _led = LED1; */
/*     break; */
/*   } */
/*   case '2': { */
/*     _led = LED2; */
/*     break; */
/*   } */
/*   case '3': { */
/*     _led = LED3; */
/*     break; */
/*   } */
/*  default: */
/*     break; */
/*   } */

/* } */

void showDateAndTime( rtc_t *config){
  uartWriteString(UART_USB, "\nFecha y hora: \t");
  printf("%d-%d-%d %d:%d:%d", config->year, config->month, config->wday,
         config->hour, config->min, config->sec);
}
/* * main */
int main(void) {
/* ** setup */
  boardConfig();
  uartConfig(UART_USB, 115200);
/* ** interrupciones */
/* ** declaracion variables  */
  char buffer[50] = "";
  rtc_t config;
  /* configurar hora en el rtc */
    config.year = 2018;
    config.month = 8;
    config.mday = 1;
    config.wday = 1;
    config.hour = 13;
    config.min = 17;
    config.sec = 0;
    rtcConfig(&config);
    delay(2000); // El RTC tarda en setear la hora, por eso el delay
/* ** bucle infinito */
  while (TRUE) {
    rtcRead( &config);
    /* Mostrar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
    showDateAndTime( &config );
    delay(1000);
    }


}

