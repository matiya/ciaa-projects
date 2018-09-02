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
/* ** printDateAndTime */
uint8_t printDateAndTime(rtc_t *config, char buffer[30]) {
  uartWriteString(UART_USB, "\n[");
  sprintf(buffer, "%d-%d %d:%d:%d", config->month,
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
printDataLCD(float temp, float hum, char * hora){

   /* convertir dato a string */
   char buffTemp[10] = "";
   char buffHum[10] = "";
   format(temp, buffTemp, 0);
   format(hum, buffHum, 0);

   /* cargar en memoria simbolos LCD */
   for (uint8_t i = 0; i < 6; i++){
     lcdCreateChar(i,simbolos[i]);
   }
   lcdClear();

   /* imprimir temperatura */
   lcdGoToXY(1,1);
   lcdData(2);
   /* lcdDelay_ms(200); */
   lcdSendStringRaw(" ");
   lcdSendStringRaw(buffTemp);

   /* imprimir humedad */
   lcdGoToXY(8,1);
   lcdData(0);
   /* lcdDelay_ms(200); */
   lcdSendStringRaw(" ");
   lcdSendStringRaw(buffHum);

   /* imprimir fecha y hora */
   lcdGoToXY(1,2);
   lcdData(4);
   /* lcdDelay_ms(200); */
   lcdSendStringRaw(" ");
   lcdSendStringRaw(hora);

   lcdDelay_ms(500);
   /* actualizar iconos */
   lcdGoToXY(1,1);
   lcdData(3);
   lcdGoToXY(8,1);
   lcdData(1);
   lcdGoToXY(1,2);
   lcdData(5);
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
    uartWriteString(UART_USB, buffer);
    /* writeToFS(buffer); */
    dht11Read( &humedad, &temperatura);
    printDataLCD(temperatura, humedad, buffer);
    /* sprintf(buffer, " %d:%d", config.hour, config.min); */
    format(temperatura, buffer, 0);
    printf(" temp: %s \t", buffer);
    format(humedad, buffer, 0);
    printf("hum: %s\n", buffer);
    delay(500);
  }
}

