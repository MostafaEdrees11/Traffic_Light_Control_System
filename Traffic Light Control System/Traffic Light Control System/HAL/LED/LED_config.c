/**
 ******************************************************************************
 * @file           : LED_config.c
 * @author         : Mostafa Edrees
 * @brief          : Configuration file of LED.
 * @date           : 10/13/2023
 * @board          : ATMEGA32
 ******************************************************************************
**/

#include "../../LIB/Error_States.h"
#include "../../LIB/stdTypes.h"

#include "LED_priv.h"
#include "LED_config.h"

#include "../../MCAL/DIO/DIO_int.h"

LED_t LED_AstrLedConfig[LED_NUM] = 
{
	{DIO_u8PORTC, DIO_u8PIN0, LED_u8SOURCE, LED_u8OFF},
	{DIO_u8PORTC, DIO_u8PIN1, LED_u8SOURCE, LED_u8OFF},
	{DIO_u8PORTC, DIO_u8PIN2, LED_u8SOURCE, LED_u8OFF},
	{DIO_u8PORTC, DIO_u8PIN3, LED_u8SOURCE, LED_u8OFF},
	{DIO_u8PORTC, DIO_u8PIN4, LED_u8SOURCE, LED_u8OFF},
	{DIO_u8PORTC, DIO_u8PIN5, LED_u8SOURCE, LED_u8OFF}
};