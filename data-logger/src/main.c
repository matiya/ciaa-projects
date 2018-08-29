#include "main.h"
#include "board.h"
#include "sapi.h"
#include "ff.h"       // <= Biblioteca FAT FS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define FILE_NAME "prueba.txt"
/* * variables globales */
static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file
/* * funciones locales */
/* ** showDateAndTime */
uint8_t printDateAndTime(rtc_t *config, char buffer[30]) {
  uartWriteString(UART_USB, "\n[");
  sprintf(buffer, "%d-%d-%d %d:%d:%d", config->year, config->month,
          config->mday, config->hour, config->min, config->sec);
  uartWriteString(UART_USB, buffer);
  uartWriteString(UART_USB, "]");
  return 0;
}
/* ** setupFS */
uint8_t setupFS(){
  if( f_mount( &fs, "", 0 ) != FR_OK ){
    uartWriteString(UART_USB, "[E] Error al montar la SD\n\r");
    return 1;
  }
  return 0;
}
/* ** writeToFS */
uint8_t writeToFS( char dato[60]){
  uint8_t rbytes;

  if( f_open(&fp, FILE_NAME, FA_WRITE | FA_OPEN_APPEND) == FR_OK){
    f_write(&fp, dato, 12, &rbytes);
    if ( rbytes==12){
      uartWriteString(UART_USB, "[I] Escritura exitosa\n");
    }
  }
  else{
    uartWriteString(UART_USB, "[E] Error al abrir la SD\n");
  }
  return 0;
}
/* ** readDHT */
uint8_t readDHT() {
  uint8_t valor = gpioRead(GPIO5);
  return valor;
}
/* ** format */
static void format( float valor, char *dst, uint8_t pos ){
	uint16_t val;
	val = 10 * valor;
	val = val % 1000;
	dst[pos] = (val / 100) + '0';
	pos++;
	dst[pos] = (val % 100) / 10 + '0';
	pos++;
	dst[pos] = '.';
	pos++;
	dst[pos] = (val % 10)  + '0';
	pos++;
	dst[pos] = '\0';
}


/* ** printDataLCD */
printDataLCD(enum simbolos simbolo, float dato){
  char buffLCD[30] = "";
  format( dato, buffLCD, 0);
  for (uint8_t i = 0; i < 8; i++){
    lcdCreateChar(i,temperatura[0].bitmap);
    lcdDelay_ms(199);
    delay(200);
    lcdData(i);
  }
switch (simbolo) {
 case temp: {
   /* cargar en memoria simbolos LCD */
   /* lcdCreateChar( 0, temp1 ); */
   /* lcdCreateChar(1, temp2); */
   /* lcdCreateChar(2, temp3); */
   /* lcdCreateChar(3, temp4); */
   /* lcdCreateChar(4, temp5); */
   /* lcdCreateChar(5, temp6); */
   /* lcdClear(); */
   /* lcdDelay_ms(199); */
   /* lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1 */
   /* lcdData(0); */
   /* delay(1000); */
   /* lcdData(1); */
   /* lcdCreateChar(6, temp7); */
   /* rotar por las animaciones */
   /* for (uint8_t i = 0; i < 2; ++i) { */
     /* lcdData(i); */
     /* lcdData(0); */
   /* } */
   /* imprimir dato */
    lcdSendStringRaw(buffLCD);
   break;
 }
 case hum: {
   /* cargar en memoria simbolos LCD */
   /* rotar por las animaciones */
   /* imprimir dato */
   break;
 }
 case time: {
   /* cargar en memoria simbolos LCD */
   /* rotar por las animaciones */
   /* imprimir dato */
   break;
 }
default:
  lcdSendStringRaw("ERROR");
   break;
 }
}
/* * main */
int main(void) {
/* ** setup */
  boardConfig();
  uartConfig(UART_USB, 115200);
  spiConfig( SPI0 );
  /* setupFS(); */
  /* el dht11 esta conectado al sensor de humedad */
  gpioConfig(GPIO5, GPIO_INPUT_PULLUP);
  /* inicializar sensor temp-humedad */
  dht11Init(GPIO5);
  /* inicializar lcd */
  lcdInit( 16, 2, 5, 8 );
/* ** interrupciones */
/* ** declaracion variables  */
  char buffer[30];
  uint8_t index = 0;
  rtc_t config;
  float humedad, temperatura;
  enum simbolos sym;
  /* configurar hora en el rtc */
  config.year = 2018;
  config.month = 8;
  config.mday = 21;
  config.wday = 3;
  config.hour = 19;
  config.min = 52;
  config.sec = 0;
  rtcConfig(&config);
  delay(1000); // El RTC tarda en setear la hora, por eso el delay
/* ** bucle infinito */
  while (TRUE) {
    rtcRead(&config);
    printDateAndTime(&config, buffer);
    /* writeToFS(buffer); */
    delay(500);
    dht11Read( &humedad, &temperatura);
    lcdClear();
    printDataLCD(temp, temperatura);
    format(temperatura, buffer, 0);
    lcdGoToXY(1, 2); 
    printf(" temp: %s \t", buffer);
    format(humedad, buffer, 0);
    printf("hum: %s\n", buffer);
    /* debugPrintString(buffer); */
    delay(1000);
  }
}

