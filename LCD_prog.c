/* * LCD_prog.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Eslam
 */
#include "LCD_init.h"

void HLCD_voidSendCommand(u8 A_u8cmd){
	/* Control Rs and R/W */
	MDIO_voidSetPinValue (Control_PORT, PIN0, LOW);
	MDIO_voidSetPinValue (Control_PORT, PIN1, LOW);
	         /* Send data */
	MDIO_voidSetPortValue(Data_PORT,A_u8cmd);
	         /*Set Pulse Enable*/
	MDIO_voidSetPinValue (Control_PORT, PIN2, HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue (Control_PORT, PIN2, LOW);
}

void HLCD_voidSendData(u8 A_u8data){
	/* Control Rs and R/W */
	MDIO_voidSetPinValue (Control_PORT, PIN0, HIGH);
	MDIO_voidSetPinValue (Control_PORT, PIN1, LOW);
	         /* Send data */
	MDIO_voidSetPortValue(Data_PORT,A_u8data);
	         /*Set Pulse Enable*/
	MDIO_voidSetPinValue (Control_PORT, PIN2, HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue (Control_PORT, PIN2, LOW);
}

void HLCD_voidInit(){
	/* Wait for more than 30 ms */
	_delay_ms(30);
	/* Function Set -> 0b00111000 */
	HLCD_voidSendCommand(FunctionSet);
	/* Wait for more than 39 micro second */
	_delay_ms(1);
	/* Diplay ON OFF control */
	HLCD_voidSendCommand(DiplayOF);
	/* Wait for more than 39 us */
	_delay_ms(1);
	/* Display clear -> 0b00000001 */
	HLCD_voidSendCommand(DisplayClear);
	/* Wait for more than 1.53ms */
	_delay_ms(2);
	/* Entry Mode -> 0b00000110 */
	HLCD_voidSendCommand(EntryMode);
}

void HLCD_voidClear(){
	HLCD_voidSendCommand(DisplayClear);
}

void HLCD_voidSaveCustomChar    (u8 A_u8CGRAMIndex, u8 A_u8Custom[]){
	HLCD_voidSendCommand(0b01000000 + (A_u8CGRAMIndex * 8));
	for(u8 counter = 0; counter < 8; counter ++){
		HLCD_voidSendData(A_u8Custom[counter]);
	}
	HLCD_voidSendCommand(0x80);
}

void HLCD_voidDisplayCustomChar (u8 A_u8CGRAMIndex){
	//first location for CGRAM = 0;
	if(A_u8CGRAMIndex < 8){
		HLCD_voidSendData(A_u8CGRAMIndex);
	}
}

void HLCD_voidSetCurser(u8 A_u8ColumnIndex, u8 A_u8RowIndex){
	switch(A_u8RowIndex){
	case 1: HLCD_voidSendCommand(0x80 + 0  + A_u8ColumnIndex - 1); break;
	case 2: HLCD_voidSendCommand(0x80 + 64 + A_u8ColumnIndex - 1); break;
	}
}

void HLCD_voidSendString(u8 *A_u8PtrString){
	u8 counter = 0;
	while(*(A_u8PtrString + counter) != '\0'){
		HLCD_voidSendData(*(A_u8PtrString + counter));
		counter++;
	}
}

void HLCD_voidSendNum(s32 A_s32Num){
	s32 L_s32Num = 1;
	u8 L_u8Char;
	if(A_s32Num == 0){
		HLCD_voidSendData('0');
	}
	if(A_s32Num < 0){
		HLCD_voidSendData('-');
		A_s32Num *= -1;
	}
	while(A_s32Num != 0){
		L_s32Num = L_s32Num * 10 + A_s32Num % 10;
		A_s32Num = A_s32Num / 10;
	}
	while(L_s32Num != 1){
		L_u8Char = L_s32Num % 10;
		HLCD_voidSendData(L_u8Char + 48);
		L_s32Num = L_s32Num / 10;
	}
}
