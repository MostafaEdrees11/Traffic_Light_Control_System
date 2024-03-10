/*
 * Traffic_System_priv.h
 *
 * Created: 3/8/2024 11:30:10 AM
 *  Author: Mostafa Edrees
 */ 


#ifndef TRAFFIC_SYSTEM_PRIV_H_
#define TRAFFIC_SYSTEM_PRIV_H_

volatile void TRAFFIC_CONTROL_StvidSwitchFromNormalToPedestrain(void *);

void Run_Normal_Mode(void);

void Run_Pedestrain_Mode(void);

void STOP(void);

void READY(void);

void GO(void);

volatile void Change_Current_Car_State(void);

typedef enum
{
	Normal_Mode,
	Pedestrain_Mode	
}MODE_STATE_t;

typedef enum
{
	CAR_RED,
	CAR_YELLOW,
	CAR_GREEN	
}CAR_STATE_t;

typedef enum
{
	PEDESTRAIN_RED = 3,
	PEDESTRAIN_YELLOW,
	PEDESTRAIN_GREEN
}PEDESTRAIN_STATE_t;


#endif /* TRAFFIC_SYSTEM_PRIV_H_ */