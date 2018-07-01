/* #include "main.h" */
/* #include "board.h" */
/* #include "sapi.h" */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* * variables globales */
uint8_t timer_counter = 0;
/* * funciones locales */
/* ** copyString */
void copyString(char *src, char *dst){
  uint8_t i = 0;
  do {
    dst[i] = src[i];
    printf("Index: %d \t char: %c\n", i, src[i]);
    i++;
  }while(src[i] != '\0');
}
/* ** exchangeCaps               */
void exchangeCaps( char *src, char *dst){
  uint8_t i = 0;
  do {
    if ((uint8_t)src[i] > 96 && (uint8_t)src[i] < 123 ) {
      dst[i] = (char) (src[i] - 32);

    }
    else{ 
      if ((uint8_t)src[i] > 64 && (uint8_t)src[i] < 91 ) {
        dst[i] = (char)(src[i] + 32);
      }
      else{
        dst[i] = src[i];
      }
    }
    i++;
  }while(src[i] != '\0');
}

/* ** joinStrings */
/************************************************************/
/* Esta función es más que insegura, no chequea los límites */
/*   de str1 ni de str2 y puede causar un segfault          */
/************************************************************/
void joinStrings(char* str1, char* str2){
  uint8_t i = 0;
  while (str1[i] != '\0'){
    i++;
  }
  for (uint8_t j = 0; str2[j] != '\0'; j++, i++){
    str1[i] = str2[j];
  }
}
/* * main */
int main(void) {
/* ** setup */
  /* Inicialización variables*/
  char source[30] = "Holis Mundis!";
  char destination[30] = "";
  char str1[50] = "Tengo espacio: ";
  char str2[50] = "acá";
/* ** main-program */
  exchangeCaps(source, destination);
  printf("String copiado: %s \n", destination);

  joinStrings(str1, str2);
  printf("Unión: %s \n", str1);
}
  
