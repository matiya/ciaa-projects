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
  struct temperatura_s {
    char bitmap[8];
  };

  struct temperatura_s temperatura[6] = {
                                         0b00100,
                                         0b00100,
                                         0b01110,
                                         0b10111,
                                         0b10111,
                                         0b10011,
                                         0b01110,
                                         0b00000
  };

  /* const char temp1[8] = { */
  /* temperatura[0] = { */
  /*                        0b00100, */
  /*                        0b00100, */
  /*                        0b01110, */
  /*                        0b10111, */
  /*                        0b10111, */
  /*                        0b10011, */
  /*                        0b01110, */
  /*                        0b00000 */
  /* }; */
  const char temp2[8] = {
                            0B01110,
                            0B01010,
                            0B01010,
                            0B01010,
                            0B01010,
                            0B10001,
                            0B11111,
                            0B01110
  };

  const uint8_t temp3[8] = {
                            0B01110,
                            0B01010,
                            0B01010,
                            0B01010,
                            0B01010,
                            0B11111,
                            0B11111,
                            0B01110
  };
  const uint8_t temp4[8] = {
                            0B01110,
                            0B01010,
                            0B01010,
                            0B01010,
                            0B01110,
                            0B11111,
                            0B11111,
                            0B01110
  };
  uint8_t const  temp5[8] = {
                            0B01110,
                            0B01010,
                            0B01010,
                            0B01110,
                            0B01110,
                            0B11111,
                            0B11111,
                            0B01110
  };
  uint8_t const  temp6[8] = {
                            0B01110,
                            0B01010,
                            0B01110,
                            0B01110,
                            0B01110,
                            0B11111,
                            0B11111,
                            0B01110
  };
  const char e_char[8] = {
                          0b01110,
                          0b10000,
                          0b10000,
                          0b01100,
                          0b01000,
                          0b10000,
                          0b10001,
                          0b01110
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
