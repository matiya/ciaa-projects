#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* * funciones locales */
/* ** showDateAndTime */
uint8_t getDateAndTime(rtc_t *config, char buffer[30]) {
  uartWriteString(UART_USB, "\nFecha y hora: \t");
  sprintf(buffer, "%d-%d-%d %d:%d:%d", config->year, config->month,
          config->mday, config->hour, config->min, config->sec);
  uartWriteString(UART_USB, buffer);
  uartWriteString(UART_USB, "\n\r");
  return 0;
}
/* * main */
int main(void) {
/* ** setup */
  boardConfig();
  uartConfig(UART_USB, 115200);
  spiConfig( SPI0 );
/* ** interrupciones */
/* ** declaracion variables  */
  char buffer[30];
  uint8_t index = 0;
  rtc_t config;
  /* configurar hora en el rtc */
  config.year = 2018;
  config.month = 8;
  config.mday = 21;
  config.wday = 3;
  config.hour = 19;
  config.min = 52;
  config.sec = 0;
  rtcConfig(&config);
  delay(2000); // El RTC tarda en setear la hora, por eso el delay
/* ** bucle infinito */
  while (TRUE) {
    rtcRead(&config);
    /* Mostrar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
    getDateAndTime(&config, buffer);
    delay(1000);
  }
}

