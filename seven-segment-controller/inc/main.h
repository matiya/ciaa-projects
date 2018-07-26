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

#define NUM_DIGITOS 3
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
bool TEC_state;
bool calc_status;
uint32_t timer;

static const uint8_t lut7segmentos[8] = {
    GPIO0, // A
    GPIO5, // B
    GPIO6, // C
    GPIO4, // D
    GPIO2, // E
    GPIO3, // F
    GPIO1  // G
};

static const uint8_t int7segmentos[10] = {
    0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b1111111,
    0b1111111, 0b1111111, 0b1111111, 0b1111111, 0b1111111};

static const uint8_t columnas[4] = {T_COL0, T_FIL2, T_FIL3, T_FIL0};
static const uint8_t filas[4] = {T_COL1, CAN_TD, CAN_RD, RS232_TXD};

static const char teclado_digitos[4][4] = {{'#', 'D', '0', '*'}, // 1ra fila
                                           {'9', 'C', '8', '7'}, // 2da fila
                                           {'6', 'B', '5', '4'},
                                           {'3', 'A', '2', '1'}};
 static const uint16_t potencias[4] = {1, 10, 100, 1000};
/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */

void changeLedState(const uint8_t);
int main(void);

void checkTECStatus(uint8_t);
/*==================[cplusplus]==============================================*/

#ifdef __cplusplus

#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _MAIN_H_ */
