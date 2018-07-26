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
/* ** scanTec */
/* Funcion que determina que caracter del teclado */
/* matricial esta activado */
char *scanTec(void) {
  char *ptr_digito = "\0";
  for (uint8_t i = 0; i < 4; ++i) {
    gpioWrite(columnas[i], ON);
    for (uint8_t j = 0; j < 4; ++j) {
      /* uartWriteString(UART_USB, "\nEn la fn"); */
      if (gpioRead(filas[j])) {
        ptr_digito = &(teclado_digitos[j][i]);
        char str[2] = "\0";
        str[0] = *ptr_digito;
        uartWriteString(UART_USB, str);
        /* espero a que se deje de presionar el digito */
        while (gpioRead(filas[j])) {
          delay(100);
        }
      }
    }
    gpioWrite(columnas[i], OFF);
  }
  return ptr_digito;
}

/* ** cycleLeds */
void cycleLEDs(gpioMap_t LED) {
  for (gpioMap_t i = LEDR; i <= LED; i++) {
    changeLedState(i);
  }
}
/* ** getNumber */
/* Funcion para obtener los tres digitos que componen un numero */
/* Toma como argumento la cantidad de digitos y devuelve el numero */
uint32_t getNumber(uint8_t nro) {
  uint32_t valor = 0;
  uint8_t contador = 0;
  char *valor_leido ="\0";
  char *debug_buffer[50];

  while (contador < nro) {
    /* uartWriteString(UART_USB, "\nValor leido: "); */
    /* uartWriteString(UART_USB, itoa((uint8_t)*valor_leido, debug_buffer,10)); */
    /* me aseguro de que lea solo un valor numerico */
    do{
      valor_leido = scanTec();
    }while ((uint8_t)*valor_leido < 48 || (uint8_t)*valor_leido > 57);
    valor = valor + (*valor_leido - 48)*potencias[nro - contador - 1];
    contador += 1;
  }
  return valor;
}
/* ** cycleLeds */
void calc(char *ptr_digito) {
  uint32_t operando1 = 0;
  uint32_t operando2 = 0;
  char debug_buffer[50];
  switch (*ptr_digito) {
  /* suma */
  case 'A': {  
    uartWriteString(UART_USB, "\n ** Modo suma ** \n");
    operando1 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " + ");
    operando2 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " = ");
    uartWriteString(UART_USB, itoa(operando1+operando2, debug_buffer,10));
    break;
  }
  /* resta */
  case 'B': {
    uartWriteString(UART_USB, "\n ** Modo resta **\n");
    operando1 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " - ");
    operando2 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " - ");
    uartWriteString(UART_USB, " = ");
    uartWriteString(UART_USB, itoa(operando1-operando2, debug_buffer,10));
    break;
  }
    /* producto */
  case 'C': {
    uartWriteString(UART_USB, "\n ** Modo producto **\n");
    operando1 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " * ");
    operando2 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " = ");
    uartWriteString(UART_USB, itoa(operando1*operando2, debug_buffer,10));
    break;
  }
    /* division */
  case 'D': {
    uartWriteString(UART_USB, "\n ** Modo division **\n");
    operando1 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " / ");
    operando2 = getNumber(NUM_DIGITOS);
    uartWriteString(UART_USB, " = ");
    uartWriteString(UART_USB, itoa(operando1/operando2, debug_buffer,10));

    break;
  }
  case '#': {
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
  /* var para guardar el digito pulsado del teclado */
  char *digitoTeclado;
  /* Habilita el puerto serie */
  uartConfig(UART_USB, 9600);
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
    digitoTeclado = scanTec();
    /* paso el control a la rutina de calculos */
    if ((uint8_t)*digitoTeclado > 64 && (uint8_t)*digitoTeclado <69) {
      uartWriteString(UART_USB, "\nIngresando modo calculadora");
      calc(digitoTeclado);
    }
          
  }
}
