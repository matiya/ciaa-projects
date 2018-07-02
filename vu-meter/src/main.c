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
/* ** cycleLeds */
void cycleLEDs(gpioMap_t LED){
  for (gpioMap_t i = LEDR; i <= LED; i++){
    changeLedState(i);
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
  uint16_t valorLeido = 0;
  /* interrupciones */
  /* tickCallbackSet(printStatus, NULL); */

  adcConfig(ADC_ENABLE);

/* ** bucle infinito */
  while (TRUE) {
/* *** control uart  */
    valorLeido = adcRead( CH1 );
    itoa(valorLeido, debug_buffer,10);
    uartWriteString(UART_USB, debug_buffer);
    uartWriteString(UART_USB, "\n");
/* *** control leds */
    if (valorLeido >= 0 && valorLeido < 256) {
      cycleLEDs(LEDB);
    }
    if (valorLeido >= 256 && valorLeido < 512) {
      cycleLEDs(LED1);
    }
    if (valorLeido >= 512 && valorLeido < 768) {
      cycleLEDs(LED2);
    }
    if (valorLeido >= 768 && valorLeido < 1024) {
      cycleLEDs(LED3);
    }
  }
}
  
