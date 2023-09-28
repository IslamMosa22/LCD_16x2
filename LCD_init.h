/*
 * LCD_init.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Eslam
 */
#ifndef HAL_LCD_INIT_H_
#define HAL_LCD_INIT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_init.h"
#include<util/delay.h>

#define F_CPU        80000000UL

#define Control_PORT PORTC
#define Data_PORT    PORTD

#define FunctionSet  0b00111100
#define DiplayOF     0b00001100
#define DisplayClear 0b00000001
#define EntryMode    0b00000110

#define LCD_LINE1 1
#define LCD_LINE2 2


void HLCD_voidInit();
void HLCD_voidSendCommand(u8 A_u8cmd);
void HLCD_voidSendData(u8 A_u8data);
void HLCD_voidClear();

void HLCD_voidSaveCustomChar    (u8 A_u8CGRAMIndex, u8 A_u8Custom[]);
void HLCD_voidDisplayCustomChar (u8 A_u8CGRAMIndex);
void HLCD_voidSetCurser(u8 A_u8ColumnIndex, u8 A_u8RowIndex);
void HLCD_voidSendString(u8 *A_u8PtrString);
void HLCD_voidSendNum(s32 A_s32Num);
#endif /* HAL_LCD_INIT_H_ */
