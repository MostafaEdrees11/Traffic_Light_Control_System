/*
 * Traffic_System_prog.c
 *
 * Created: 3/8/2024 11:29:43 AM
 *  Author: Mostafa Edrees
 */ 

#include "../LIB/stdTypes.h"
#include "../LIB/Error_States.h"

#include "../HAL/LED/LED_config.h"
#include "../HAL/LED/LED_int.h"

#include "../HAL/LCD/LCD_config.h"
#include "../HAL/LCD/LCD_int.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../MCAL/EXTI/EXTI_config.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include "../MCAL/GIE/GIE_int.h"

#include "../MCAL/TIMER0/TIMER0_config.h"
#include "../MCAL/TIMER0/TIMER0_int.h"

#include "../MCAL/interrupt.h"

#include "Traffic_System_config.h"
#include "Traffic_System_priv.h"

extern EXTI_Configuration_t EXTI_AStrEXTI_Config[MAX_NUM_EXTI];
extern LED_t LED_AstrLedConfig[LED_NUM];

MODE_STATE_t state;
CAR_STATE_t curr_car;
CAR_STATE_t prev_car;
PEDESTRAIN_STATE_t curr_pedestrain;

u8 flag;

volatile void TRAFFIC_CONTROL_StvidSwitchFromNormalToPedestrain(void *p)
{
	state = Pedestrain_Mode;
}

ES_t TRAFFIC_CONTROL_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	LCD_enuInit();
	
	TIMER0_enuInit();
	
	DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8INPUT);
	DIO_enuSetPinVal(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PULL_UP);
	
	EXTI_enuInit(EXTI_AStrEXTI_Config);
	EXTI_enuEnable(EXTI0);
	EXTI_enuCallBackFunc(&TRAFFIC_CONTROL_StvidSwitchFromNormalToPedestrain, NULL,EXTI0);
	
	LED_enuINIT(LED_AstrLedConfig);
	
	state = Normal_Mode;
	prev_car = CAR_RED;
	curr_car = CAR_RED;
	flag = 1;
	
	TIMER0_enuEnableOVFInterrupt();
	
	GIE_enuGloable_Interrupt_Enable();
	
	return Local_enuErrorState;
}


ES_t TRAFFIC_CONTROL_enuRunSystem(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	switch(state)
	{
		case Normal_Mode:
		Run_Normal_Mode();
		break;
		
		case Pedestrain_Mode:
		Run_Pedestrain_Mode();
		break;
	}
	
	return Local_enuErrorState;
}

void Run_Normal_Mode(void)
{
	if(flag)
	{
		LED_enuTurnOFF(&LED_AstrLedConfig[prev_car]);
		LED_enuTurnON(&LED_AstrLedConfig[curr_car]);
		TIMER0_enuDelayMilliSecondASyn(3500, (void (*)(void*))&Change_Current_Car_State, NULL);
		flag = 0;
	}
}

volatile void Change_Current_Car_State(void)
{
	flag = 1;
	
	switch(curr_car)
	{
		case CAR_RED:
		prev_car = curr_car;
		curr_car = CAR_YELLOW;
		break;
		
		case CAR_YELLOW:
		if(prev_car == CAR_RED)
		{
			prev_car = curr_car;
			curr_car = CAR_GREEN;
		}
		else if(prev_car == CAR_GREEN)
		{
			prev_car = curr_car;
			curr_car = CAR_RED;
		}
		break;
		
		case CAR_GREEN:
		prev_car = curr_car;
		curr_car = CAR_YELLOW;
		break;
	}
	
	LCD_vidClearScreen();
	LED_enuTurnOFF(&LED_AstrLedConfig[curr_pedestrain]);
}

void Run_Pedestrain_Mode(void)
{
	GIE_enuGloable_Interrupt_Disable();
	
	switch(curr_car)
	{
		case CAR_RED:
		GO();
		break;
		
		case CAR_GREEN:
		case CAR_YELLOW:
		STOP();
		READY();
		GO();
		break;
	}
	
	state = Normal_Mode;
	prev_car = CAR_RED;
	curr_car = CAR_YELLOW;
	flag = 1;
	
	GIE_enuGloable_Interrupt_Enable();
}

void STOP(void)
{
	LCD_vidClearScreen();
	LCD_enuWriteString((u8 *)"     STOP!!     ");
	curr_pedestrain = PEDESTRAIN_RED;
	LED_enuTurnON(&LED_AstrLedConfig[curr_pedestrain]);
	TIMER0_enuDelayMilliSecondSyn(2000);
}

void READY(void)
{
	LCD_vidClearScreen();
	LCD_enuWriteString((u8 *)"     #READY     ");
	LED_enuTurnOFF(&LED_AstrLedConfig[curr_car]);
	LED_enuTurnOFF(&LED_AstrLedConfig[curr_pedestrain]);
	curr_pedestrain = PEDESTRAIN_YELLOW;
	curr_car = CAR_YELLOW;
	LED_enuTurnON(&LED_AstrLedConfig[curr_car]);
	LED_enuTurnON(&LED_AstrLedConfig[curr_pedestrain]);
	TIMER0_enuDelayMilliSecondSyn(3500);
}
void GO(void)
{
	LCD_vidClearScreen();
	LCD_enuWriteString((u8 *)"     $$GO$$     ");
	LED_enuTurnOFF(&LED_AstrLedConfig[curr_car]);
	LED_enuTurnOFF(&LED_AstrLedConfig[curr_pedestrain]);
	curr_car = CAR_RED;
	curr_pedestrain = PEDESTRAIN_GREEN;
	LED_enuTurnON(&LED_AstrLedConfig[curr_car]);
	LED_enuTurnON(&LED_AstrLedConfig[curr_pedestrain]);
	TIMER0_enuDelayMilliSecondSyn(3500);
}
