#include "main.h"
#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* * variables globales */
gpioMap_t _led = 0;
uint16_t _delay = 0;
static const uint16_t delay_list[4] = {50, 100, 200, 800};
/* * funciones locales */
/* ** changeLedState */
void updateLeds() {
  gpioToggle(_led);
  delay(_delay);
}
/* ** scanTec */
void scanTec(){
  for (gpioMap_t i = TEC1; i < TEC4 + 1; i++){
    if(!(gpioRead(i))){
      _delay = delay_list[i - TEC1];
    }
  }
  return 0;
}
/* ** readUart */
void readUart() {
  uint8_t received;
  uartReadByte(UART_USB, &received);
    
  switch (received) {
  case 'a': {
    _led = LEDB;
    break;
  }
  case '1': {
    _led = LED1;
    break;
  }
  case '2': {
    _led = LED2;
    break;
  }
  case '3': {
    _led = LED3;
    break;
  }
 default:
    break;
  }

}

/* * main */
int main(void) {
/* ** setup */
  boardConfig();
  uartConfig(UART_USB, 115200);
/* ** interrupciones */
  uartRxInterruptSet(UART_USB, true);
  uartRxInterruptCallbackSet( UART_USB, readUart);
/* ** declaracion variables  */
  char buffer[50] = "";
/* ** bucle infinito */
  while (TRUE) {
    scanTec();
    readUart();
    updateLeds();
  }
}
