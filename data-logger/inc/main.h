/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _MAIN_H_
#define _MAIN_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"
/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
  const char temperatura[6][8] = {
      {0B01110, 0B01010, 0B01010, 0B01010, 0B01010, 0B10001, 0B10001, 0B01110},
      {0B01110, 0B01010, 0B01010, 0B01010, 0B01010, 0B10001, 0B11111, 0B01110},
      {0B01110, 0B01010, 0B01010, 0B01010, 0B01010, 0B11111, 0B11111, 0B01110},
      {0B01110, 0B01010, 0B01010, 0B01010, 0B01110, 0B11111, 0B11111, 0B01110},
      {0B01110, 0B01010, 0B01010, 0B01110, 0B01110, 0B11111, 0B11111, 0B01110},
      {0B01110, 0B01110, 0B01110, 0B01110, 0B01110, 0B11111, 0B11111, 0B01110}
  };

  const char hora[7][8] = {
      {0B00100, 0B00100, 0B00100, 0B00111, 0B00000, 0B00000, 0B00000, 0B00000},
      {0B00100, 0B00100, 0B00100, 0B00100, 0B00010, 0B00001, 0B00000, 0B00000},
      {0B00000, 0B00001, 0B00010, 0B00100, 0B00100, 0B00100, 0B00100, 0B00000},
      {0B00000, 0B00000, 0B00000, 0B00111, 0B01000, 0B10000, 0B00000, 0B00000},
      {0B00000, 0B00000, 0B00000, 0B11100, 0B00010, 0B00001, 0B00000, 0B00000},
      {0B00000, 0B10000, 0B01000, 0B00100, 0B00100, 0B00100, 0B00100, 0B00000},
      {0B00100, 0B00100, 0B00100, 0B11100, 0B00000, 0B00000, 0B00000, 0B00000},
  };
  const char simbolos[6][8] = {
      {0B00100, 0B00100, 0B01110, 0B01110, 0B11011, 0B11101, 0B11011,
       0B01110}, // 0 - gota llena
      {0B00100, 0B00100, 0B01110, 0B01010, 0B10001, 0B10001, 0B11011,
       0B01110}, // 1 - gota vacia
      {0B01110, 0B01010, 0B01010, 0B01010, 0B10001, 0B10001, 0B11111,
       0B01110}, // 2 - termometro vacio
      {0B01110, 0B01010, 0B01110, 0B01110, 0B11111, 0B11111, 0B11111,
       0B01110}, // 3 - termometro lleno
      {0B00100, 0B00100, 0B00100, 0B00100, 0B00010, 0B00001, 0B00000,
       0B00000}, // 4 - reloj1
      {0B00000, 0B10000, 0B01000, 0B00100, 0B00100, 0B00100, 0B00100,
       0B00100}, // 5 - reloj2
  };
  enum simbolos {temp, hum, time, num_simbolos};
/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */

int main(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
