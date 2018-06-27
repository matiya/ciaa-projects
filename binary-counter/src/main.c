//#include
#include "board.h"
#include "sapi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t stack[4];

/* * Funciones Locales */
/* ** Debounce */
void debounce(gpioMap_t tecla) {
  bool TEC_state = true;
  while (TEC_state) {
    if (gpioRead(tecla)) {
      delay(100);
      TEC_state = false;
    }
  }
}

/* ** DecToBin */
void DecToBin(uint8_t num) {
  uint8_t index = 0;
  uint8_t rest = 0;
  while (num > 1) {
    rest = num % 2;
    num = (uint8_t)num / 2;
    *(stack + index) = rest;
    index++;
  }
  if (num == 1) {
    *(stack + index) = 1;
  }
}
/* * Main */
void main(void) {

/* ** Setup */
  /* *** Config Gral */
  boardConfig();

  /* *** Config ADC */
  adcConfig( ADC_ENABLE ); /* ADC */
  dacConfig( DAC_ENABLE ); /* DAC */
  /* Variable para almacenar el valor leido del ADC CH1 */
  uint16_t muestra = 0;
  /* Variables de delays no bloqueantes */
  delay_t delay1;
  delay_t delay2;

  /* Inicializar Retardo no bloqueante con tiempo en ms */
  delayConfig( &delay1, 500 );
  delayConfig( &delay2, 200 );

/* *** Config Servo */
  servoConfig(1, SERVO_ENABLE);
  servoConfig(SERVO1, SERVO_ENABLE_OUTPUT);
  uint8_t anguloServo;
/* *** Config UART */
  /* Inicializar UART_USB a 115200 baudios */
  uartConfig(UART_USB, 115200);

  DEBUG_PRINT_ENABLE
  debugPrintConfigUart(UART_USB, 115200);
  debugPrintString("Iniciando......\n");
  // Habilita cuenta de tick cada 1ms
  tickConfig(1);
  uint8_t counter = 0;


  // Variable para guardar dato entrada;
  static uint8_t datoRx;
  /* consolePrintConfigUart(UART_USB, 115200); */

  // Buffer para string de DEBUG
  char debug_buffer[50];
 
  // Inicializaciones del usuario prueba
  gpioConfig(0, GPIO_ENABLE);
  gpioConfig(LEDR, GPIO_OUTPUT);
  gpioConfig(LEDG, GPIO_OUTPUT);
  gpioConfig(LEDB, GPIO_OUTPUT);
  gpioConfig(LED1, GPIO_OUTPUT);
  gpioConfig(LED2, GPIO_OUTPUT);
  gpioConfig(LED3, GPIO_OUTPUT);
  gpioConfig(TEC1, GPIO_INPUT);
  gpioConfig(TEC2, GPIO_INPUT);

 
/* ** For ever ever */
  while (TRUE) {
/* *** UART */
    if (!gpioRead(TEC1)) {
      counter++;
      debounce(TEC1);
      uartWriteString(UART_USB, "Presionado TEC1.\t Contador: ");
      debugPrintIntFormat(counter, 10);
      uartWriteString(UART_USB, "\n");
    }
    if (!gpioRead(TEC2)) {
      counter--;
      debounce(TEC2);
      uartWriteString(UART_USB, "Presionado TEC2.\t Contador: ");
      debugPrintIntFormat(counter, 10);
      uartWriteString(UART_USB, "\n");
    }
    if (counter >= 15 || counter <= 0)
      counter = 0;

    if (!gpioRead(TEC2)) {
      uartReadByte( UART_USB, &datoRx);
      debugPrintIntFormat(datoRx, 10);
      debounce(TEC2);
   }
    if (uartReadByte( UART_USB, &datoRx)){
      uartWriteString(UART_USB, "Recibido algo: \n");
      uartWriteString(UART_USB, datoRx);
      /* uartRxRead(UART_USB); */
    }
/* *** UART Debug */
    /* if (uartRxReady(UART_USB)) { */
    /*   debugPrintString("Recibido algoINC\n"); */
    /*   if (receiveBytesUntilReceiveStringOrTimeoutBlocking( */
    /*           UART_USB, "INC", 4, debug_buffer, 50, 100)) */
    /*     debugPrintString("Recibido INC\n"); */
    /*   else */
    /*     debugPrintString("NO Recibido INC\n"); */
    /* } */
    /* debugPrintIntFormat( stack[0], 10); */
    /* debugPrintIntFormat( stack[1], 10); */
    /* debugPrintIntFormat( stack[2], 10); */
    /* debugPrintIntFormat( stack[3], 10); */
    /* uartWriteString( UART_USB, "\n Contador: "); */
    /* debugPrintIntFormat( counter, 10); */
    /* uartWriteString( UART_USB, "\n"); */
    DecToBin(counter);
    for (int i = 3; i > -1; i--) {
      /* negado porque en la variable stack */
      /*   los valores se encuentran de MSB a LSB */
      if (stack[i])
        gpioWrite(LEDB + 3 - i, ON);
      else
        gpioWrite(LEDB + 3 - i, OFF);
    }
/* *** Control de Motor - Joystick */
    /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
    if ( delayRead( &delay1 ) ){

      /* Leo la Entrada Analogica AI0 - ADC0 CH1 */
      muestra = adcRead( CH1 );

      /* Envío la primer parte del mnesaje a la Uart */
      /* uartWriteString( UART_USB, "ADC CH1 value: " ); */

      /* Conversión de muestra entera a ascii con base decimal */
      itoa( muestra/2, debug_buffer, 10 ); /* 10 significa decimal */

      /* Enviar muestra y Enter */
      /* uartWriteString( UART_USB, debug_buffer ); */
      /* uartWriteString( UART_USB, ";\r\n" ); */


      servoWrite(SERVO1, muestra/(1023/180));
    }

   
  }
}
