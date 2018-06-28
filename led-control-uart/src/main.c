#include "main.h"
#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* * variables globales */
uint8_t timer_counter = 0;
/* * funciones locales */
/* ** changeLedState */
void changeLedState(const uint8_t LED) {
  gpioWrite(LED, ON);
  delay(400);
  gpioWrite(LED, OFF);
}
/* ** checkTECStatus */
void checkTECStatus(gpioMap_t TEC) {
  if (!gpioRead(TEC)) {
    TEC_state = !TEC_state;
  }
}
/* ** clearScreen */
void clearScreen(){
  uartWriteByte(UART_USB, 27);
  uartWriteByte(UART_USB, '[');
  uartWriteByte(UART_USB, '2');
  uartWriteByte(UART_USB, 'J');
}
/* ** printStatus */
void printStatus(void) {
  if (timer_counter < 100){
    timer_counter++;
    return ;
  }
  clearScreen();
  uartWriteString(UART_USB, "\n******* STATUS *******\n");
  for (uint8_t i = LEDR; i < LED3 + 1; i++) {
    if (gpioRead(i)) {
      uartWriteString(UART_USB, LED_NAMES[i - LEDR]);
      uartWriteString(UART_USB, ": ON \t");
    } else {
      uartWriteString(UART_USB, LED_NAMES[i - LEDR]);
      uartWriteString(UART_USB, ": OFF \t");
    }
  }
  uartWriteString(UART_USB, "\n");
  for (uint8_t i = TEC1; i < TEC4 + 1; i++) {
    if (!gpioRead(i)){
      uartWriteString(UART_USB, TEC_NAMES[i - TEC1]);
      uartWriteString(UART_USB, ": ON \t");
    } else {
      uartWriteString(UART_USB, TEC_NAMES[i - TEC1]);
      uartWriteString(UART_USB, ": OFF \t");
    }
  }

  timer_counter = 0;
}
/* ** writeToUART */
void writeToUART(uint8_t received) {
  uartReadByte(UART_USB, &received);
  /* uartWriteString(UART_USB, "\nRecibido: "); */
  /* itoa(received, debug_buffer, 10); */
  /* uartWriteString(UART_USB, debug_buffer); */
    
  switch (received) {
  case 'a': {
    gpioToggle(LEDB);
    break;
  }
  case 'v': {
    gpioToggle(LEDG);
    break;
  }
  case 'r': {
    gpioToggle(LEDR);
    break;
  }
  case '1': {
    gpioToggle(LED1);
    break;
  }
  case '2': {
    gpioToggle(LED2);
    break;
  }
  case '3': {
    gpioToggle(LED3);
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
  /* Inicialización variables*/
  TEC_state = false;
  /* Habilita cuenta de tick cada 1ms */
  tickConfig(50);
  /* pongo el timer a cero */
  timer = 0;
  /* Habilita el puerto serie */
  uartConfig(UART_USB, 115200);
  /* Inicializaciones del usuario prueba */
  gpioConfig(0, GPIO_ENABLE);
  /* Buffer para string de DEBUG */
  char debug_buffer[50];
  uint8_t received = 0;
  /* interrupciones */
  tickCallbackSet(printStatus, NULL);
  uartRxInterruptSet(UART_USB, true);
  uartRxInterruptCallbackSet( UART_USB, writeToUART);
/* ** bucle infinito */
  while (TRUE) {
/* *** TickCallback  */
    writeToUART(received);
    /* *** Prender y apagar leds */
    /* checkTECStatus(TEC1); */
  /*   if (TEC_state) { */
  /*     for (uint8_t i = LEDB; i < LED3 + 1; i++) { */
  /*       changeLedState(i); */
  /*       checkTECStatus(TEC1); */
  /*       itoa(i, debug_buffer, 10); */
  /*     } */
  /*   } */

  /*   else { */
  /*     for (uint8_t i = LED3; i > LEDG; i--) { */
  /*       changeLedState(i); */
  /*       checkTECStatus(TEC1); */
  /*     } */
  /*   } */
  /*   checkTECStatus(TEC1); */
  }
}
  
