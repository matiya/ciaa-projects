#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* * Variables globales */
bool TEC1_state = false;
uint32_t timer;
/* * Funciones locales */
/* ** changeLedState */
void changeLedState(const int LED) {
  gpioWrite(LED, ON);
  delay(400);
  gpioWrite(LED, OFF);
}
/* ** checkTEC1Status */
void checkTEC1Status(void) {
  if (!gpioRead(TEC1)) {
    TEC1_state = !TEC1_state;
    uartWriteString(UART_USB, "Cambiado Estado \n");
    if (TEC1_state)
      uartWriteString(UART_USB, "A Verdadero \n");
    else
      uartWriteString(UART_USB, "A Falso \n");
  }
}
/* ** timerInterrupt */
void timerInterrupt (void){
  timer++;
}
/* * Main */
int main(void) {
/* ** Inicialización */
  boardConfig();

  /* Habilita cuenta de tick cada 1ms */
  tickConfig(1);
  /* pongo el timer a cero */
  timer = 0;
  /* Habilita el puerto serie */
  uartConfig( UART_USB, 115200 );
  /* Inicializaciones del usuario prueba */
  gpioConfig(0, GPIO_ENABLE);
  gpioConfig(LEDG, GPIO_OUTPUT);
  gpioConfig(TEC1, GPIO_INPUT);

  /* Buffer para string de DEBUG */
  char debug_buffer[50];

/* ** Bucle infinito */
  while (TRUE) {
/* *** TickCallback  */
    tickCallbackSet( timerInterrupt, NULL );
/* *** Prender y apagar leds */
    checkTEC1Status();
    if (TEC1_state) {
      for (int i = LEDB; i < LED3 + 1; i++) {
        changeLedState(i);
        checkTEC1Status();
        itoa(i, debug_buffer, 10);
      }
    }

    else {
      for (int i = LED3; i > LEDG; i--) {
        changeLedState(i);
        checkTEC1Status();
      }
    }
    checkTEC1Status();
/* *** Imprimir el valor del timer  */
    uartWriteString(UART_USB, "Tiempo desde inicio: ");
    itoa(timer/1000, debug_buffer, 10);
    uartWriteString(UART_USB, debug_buffer);
    uartWriteString(UART_USB, "\n");
  }
}
