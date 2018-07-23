#include "main.h"
#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* * variables globales */
uint8_t timer_counter = 0;
isCalc = OFF;

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
/* ** scanTec */
char *scanTec(void) {
  for (uint8_t i = 0; i < 4; ++i) {
    gpioWrite(columnas[i], ON);
    for (uint8_t j = 0; j < 4; ++j) {
      if (gpioRead(filas[j])) {
        uartWriteString(UART_USB, "\n Presionado: ");
        uartWriteString(UART_USB, "\t");
        char *ptr_digitos = &(teclado_digitos[j][i]);
        char str[2] = "\0";
        str[0] = *ptr_digitos;
        uartWriteString(UART_USB, str);
        calc(ptr_digitos);
        /* espero a que se deje de presionar el digito */
        while (gpioRead(filas[j])) {
          delay(100);
        }

        return ptr_digitos;
      }
    }
  }
}

/* ** cycleLeds */
void) cycleLEDs(gpioMap_t LED) {
  for (gpioMap_t i = LEDR; i <= LED; i++) {
    changeLedState(i);
  }
}
/* ** getDigit */
void getDigit(uint8_t nro) {
  uint16_t valor = 0;
  uint8_t contador = 0;
  while (contador < nro) {
    if (gpioRead(filas[0]) || gpioRead(filas[1]) || gpioRead(filas[2]) ||
        gpioRead(filas[3])){
      contador += 1;
      valor_leido = 
      valor = valor + valor_leido*potencias[i];
    }
  }
}
/* ** cycleLeds */
void calc(char *ptr_digito) {
  uint8_t operando1 = 0;
  uint8_t operando2 = 0;
  switch (*ptr_digito) {
  case 'A': {
    uartWriteString(UART_USB, "\n Modo suma: \t");
    getDigit(NUM_DIGITOS);
    break;
  }
  case 'B': {
    uartWriteString(UART_USB, "\n Modo resta: \t");
    break;
  }
  case 'C': {
    uartWriteString(UART_USB, "\n Modo producto: \t");
    break;
  }
  case 'D': {
    uartWriteString(UART_USB, "\n División: \t");
    break;
  }
  case '#': {
    isCalc = OFF;
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
  /* Inicializaciones de los GPIOs*/
  for (uint8_t i = 0; i < 7; i++) {
    gpioConfig(lut7segmentos[i], GPIO_OUTPUT);
  }
  for (uint8_t i = 0; i < 4; i++) {
    gpioConfig(columnas[i], GPIO_OUTPUT);
  }
  for (uint8_t i = 0; i < 4; i++) {
    gpioConfig(filas[i], GPIO_INPUT_PULLDOWN);
  }

  /* Buffer para string de DEBUG */
  char debug_buffer[50];
  /* interrupciones */
  /* tickCallbackSet(printStatus, NULL); */

  /* ** bucle infinito */
  while (TRUE) {

/* *** decoder-7-segmentos */
    if (!gpioRead(TEC1)) {
      uint8_t digito_binario = int7segmentos[0];

      for (uint8_t i = 0; i < 9; i++) {
        if (!(digito_binario & (0b00000001 << i))) {
          gpioWrite(lut7segmentos[6 - i], 1);
          delay(100);
        }
      }
    }

/* *** control-teclado */
    for (uint8_t i = 0; i < 4; ++i) {
      gpioWrite(columnas[i], ON);
      for (uint8_t j = 0; j < 4; ++j) {
        if (gpioRead(filas[j]) && !isCalc) {
          uartWriteString(UART_USB, "\n Presionado: ");
          uartWriteString(UART_USB, "\t");
          char *ptr_digitos = &(teclado_digitos[j][i]);
          char str[2] = "\0";
          str[0] = *ptr_digitos;
          uartWriteString(UART_USB, str);
          calc(ptr_digitos);
          /* espero a que se deje de presionar el digito */
          while( gpioRead(filas[j])){
            delay(100);
          }
          /* paso el control a la rutina de calculos */

          if ((uint8_t)*ptr_digitos > 64 && (uint8_t)*ptr_digitos <69) {
            uartWriteString(UART_USB, "\nOperación : ");
            calc(ptr_digitos);
          }
          
          isCalc = OFF;
        }
      }
      gpioWrite(columnas[i], OFF);
    }
  }
}
