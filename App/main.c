///*
// * main.c
// *
// *  Created on: Oct 3, 2023
// *      Author: Lenovo
// */
//
//
#include <util/delay.h>.
#include <avr/interrupt.h>


#define F_CPU 8000000UL
#include "../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "../MCAL/GIE-DRIVER/GIE_MCAL_Interface.h"
#include "../MCAL/EXTI-DRIVER/EXTI_MCAL_Interface.h"
#include "../MCAL/ADC-DRIVER/ADC_MCAL_Interface.h"
#include "../MCAL/TMR-DRIVER/TMR_MCAL_Interface.h"
#include "../MCAL/USART-DRIVER/USART_MCAL_Interface.h"

#include "../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "../HAL/SEGMENT_DRIVER/SEG_HAL_Interface.h"
#include "../HAL/KPD_DRIVER/KPD_HAL_Interface.h"
#include "../HAL/LM_SENSOR-DIRVER/LM_HAL_Interface.h"
#include "../HAL/STEPPER_MOTOR-DRIVER/STEP_HAL_Interface.h"

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"



u8 i_1;
u8 i_2;
u8 i_3;
u8 i_4;
u8 i_5;
u8 i_6;

u8 min_left,min_right;
u8 sec_left,sec_right;
u8 hr_left,hr_right;
u8 sec;
u8 min;
u8 hr;
u8 sec_Count;
u8 i;
u8 flag;
u8 alarm_flag;
void Display(void);
void TMR0_S(void);
int main() {
	DIO_SetPortDirection(DIO_PORTA, DIO_OUTPUT);
	DIO_SetPortDirection(DIO_PORTB, DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN0,DIO_OUTPUT);
	LCD_Init();
	KPD_Init();
	u8 x;
	GIE_Enable();
	TMR0_CTC_Init(OC0_Disconnected, 125);
	TMR0_CTC_SetCallBack(&TMR0_S);
	Display();
	while (1) {
		x = KPD_GetKey();
		if (x != 0b11111111) {
			if(alarm_flag)
			{
				 sec = 0;
				                min = 0;
				                hr = 0;
				                i_1 = 0;
				                i_2 = 0;
				                i_3 = 0;
				                i_4 = 0;
				                i_5 = 0;
				                i_6 = 0;
				                alarm_flag = 0;
				                LCD_ClearDisplay();
				                Display();
			}
			if (x >= '0' && x <= '9') {
				if (i_1 == 0) {
					hr = hr * 10 + (x - '0');
					i_1 = x;
					LCD_SetPosition(0, 0);
					LCD_SendChar(i_1);
					LCD_SetPosition(1, 0);
					LCD_SendString(" ");
					LCD_SetPosition(1, 1);
					LCD_SendString("^");
					i_1++;
				} else if (i_2 == 0) {
					hr = hr * 10 + (x - '0');
					i_2 = x;
					LCD_SetPosition(0, 1);
					LCD_SendChar(i_2);
					LCD_SetPosition(1, 1);
					LCD_SendString(" ");
					LCD_SetPosition(1, 3);
					LCD_SendString("^");
					i_2++;
				} else if (i_3 == 0) {
					min = min * 10 + (x - '0');
					i_3 = x;
					LCD_SetPosition(0, 3);
					LCD_SendChar(i_3);
					LCD_SetPosition(1, 3);
					LCD_SendString(" ");
					LCD_SetPosition(1, 4);
					LCD_SendString("^");
					i_3++;
				} else if (i_4 == 0) {
					min = min * 10 + (x - '0');
					i_4 = x;
					LCD_SetPosition(0, 4);
					LCD_SendChar(i_4);
					LCD_SetPosition(1, 4);
					LCD_SendString(" ");
					LCD_SetPosition(1, 6);
					LCD_SendString("^");
					i_4++;
				} else if (i_5 == 0) {
					sec = sec * 10 + (x - '0');
					i_5 = x;
					LCD_SetPosition(0, 6);
					LCD_SendChar(i_5);
					LCD_SetPosition(1, 6);
					LCD_SendString(" ");
					LCD_SetPosition(1, 7);
					LCD_SendString("^");
					i_5++;
				} else if (i_6 == 0) {
					sec = sec * 10 + (x - '0');
					i_6 = x;
					LCD_SetPosition(0, 7);
					LCD_SendChar(i_6);
					i_6++;
				}
			}
			if(x == 'c')
			{
				sec = 0;
				min =0;
				hr =0;
				i_1 =0;
				i_2 =0;
				i_3 =0;
				i_4 =0;
				i_5 =0;
				i_6 =0;
				LCD_ClearDisplay();
				Display();
			}
			if(x == '=')
			{
				TMR0_CTC_ENABLE();
			}
		}
	}
	return 0;
}
void Display(void) {
	LCD_SetPosition(0, 0);
	LCD_SendChar('0');
	LCD_SetPosition(0, 1);
	LCD_SendChar('0');
	LCD_SetPosition(0, 2);
	LCD_SendChar(':');
	LCD_SetPosition(0, 3);
	LCD_SendChar('0');
	LCD_SetPosition(0, 4);
	LCD_SendChar('0');
	LCD_SetPosition(0, 5);
	LCD_SendChar(':');
	LCD_SetPosition(0, 6);
	LCD_SendChar('0');
	LCD_SetPosition(0, 7);
	LCD_SendChar('0');
	LCD_SetPosition(1, 0);
	LCD_SendString("^");
}
void TMR0_S(void) {

	if (sec > 60) {
		sec = 60;
	}
	if (hr > 24) {
		hr = 24;
	}
	if (min > 60) {
		min = 60;
	}
	static u16 counter = 0;

	counter++;

	if (counter == 1000)
	{
		LCD_ClearDisplay();
		LCD_SendChar((hr < 10) ? '0' : (hr / 10) + '0');
		LCD_SendChar((hr % 10) + '0');
		LCD_SendChar(':');
		LCD_SendChar((min < 10) ? '0' : (min / 10) + '0');
		LCD_SendChar((min % 10) + '0');
		LCD_SendChar(':');
		LCD_SendChar((sec < 10) ? '0' : (sec / 10) + '0');
		LCD_SendChar((sec % 10) + '0');



		if (sec > 0)
		{
		    sec--;
		}
		else if (min > 0)
		{
		    min--;
		    sec = 59; // Set sec to 59 seconds when transitioning from 0 seconds
		}
		else if (hr > 0)
		{
		    hr--;
		    min = 59;
		    sec = 59; // Set min and sec to 59 when transitioning from 0 minutes
		}
		else
		{
			alarm_flag =1;
		    LCD_ClearDisplay();
		    LCD_SetPosition(0,7);
		    LCD_SendString("Alarm");
		    DIO_SetPinValue(DIO_PORTC, DIO_PIN0, DIO_HIGH);
		    TMR0_CTC_DISABLE();
		}
		counter = 0;

	}

}




