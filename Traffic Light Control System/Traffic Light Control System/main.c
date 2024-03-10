/*
 * Traffic Light Control System.c
 *
 * Created: 3/8/2024 11:24:53 AM
 * Author : Mostafa Edrees
 */ 

#include "LIB/Error_States.h"
#include "LIB/stdTypes.h"

#include "APP/Traffic_System_config.h"
#include "APP/Traffic_System_int.h"

int main(void)
{	
	TRAFFIC_CONTROL_enuInit();

    /* Replace with your application code */
    while (1) 
    {
		TRAFFIC_CONTROL_enuRunSystem();
    }
}

