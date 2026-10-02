/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */


#include "main.h"
#include "A_os_includes.h"

#ifndef	SAMPLE_PROCESSES_ENABLED

VERSIONING	uint8_t	app_name[16] 		= "Encoder 01";
VERSIONING	uint8_t	app_version[16] 	= "1.0.0";
VERSIONING	uint8_t	a_version[32] 		= A_OS_VERSION;

extern	void process_1_init(uint32_t process_id);	//This is process1 init
extern	void process_1(uint32_t process_id);	//This is process1

extern	void process_2_init(uint32_t process_id);	//This is process2
extern	void process_2(uint32_t process_id);	//This is process2
extern	void process_3(uint32_t process_id);	//This is process3
extern	void process_4(uint32_t process_id);	//This is process4 of the application


__attribute__ ((aligned (32)))	USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = process_1,
				.user_init = process_1_init,
				.stack_size = 4096,
		},
		{
				.user_process = process_2,
				.user_init = process_2_init,
				.stack_size = 2048,
		},
		{
				.user_process = process_3,
				.stack_size = 256,
		},
		{
				.user_process = process_4,
				.stack_size = 256,
		}
};

uint8_t 	led_cntr = 0;

void process_led(void)
{
	switch(led_cntr)
	{
	case 7:
	case 9:
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
		break;
	default :
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
		break;
	}
	led_cntr++;
	if ( led_cntr >= 10 )
		led_cntr = 0;
}
#endif // #ifndef	SAMPLE_PROCESSES_ENABLED
