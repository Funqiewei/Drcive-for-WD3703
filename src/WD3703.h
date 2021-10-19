/*
 * WD3703.h
 *
 *  Created on: 2021骞�7鏈�2鏃�
 *      Author: zhoushuguang
 */

#ifndef WD3703_DRIVE_WD3703_H_
#define WD3703_DRIVE_WD3703_H_
//#include "config.h"
#include <msp430.h>

#define SKIP_ROM                0xcc
#define Convert_T           0x44
#define READ_SCRATCHPAD 0xbe

#define WD3703_Data_in                    P1DIR&=~BIT5;
#define WD3703_Data_out                   P1DIR|=BIT5;

#define WD3703_Write_High  P1OUT|=BIT5;
#define WD3703_Write_Low   P1OUT&=~BIT5;
#define H_L                P1IN&BIT5

void _delay_ms(unsigned int  nTimes);
void _delay_us(unsigned int  nTimes);
unsigned int  WD3703_Reset(void);
void WD3703_Write_Byte(unsigned char Data_in);
float WD3703_Read_Temperature(void);
char WD3703_Read_Byte(void);
//void Read_ROM_ID(void);

#endif /* WD3703_DRIVE_WD3703_H_ */
