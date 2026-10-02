/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : A_os
*/
/*
 * process_1.c
 *
 *  Created on: Jan 10, 2025
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifndef SAMPLE_PROCESSES_ENABLED

#include "ov.h"

#define	BT_UART_RX_BUF_SIZE	512
#define	BT_UART_TX_BUF_SIZE	512
uint8_t	BT_uart_rx_buffer[BT_UART_RX_BUF_SIZE];
uint8_t	BT_uart_tx_buffer[BT_UART_TX_BUF_SIZE];

UART_DriverStruct_t BT_Uart_Drv =
{
	.data = BT_uart_rx_buffer,
	.rx_max_len = BT_UART_RX_BUF_SIZE,
	.uart = &huart3,
	.wakeup_id = WAKEUP_FROM_UART3_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

#define	ENCODER_UART_RX_BUF_SIZE	512
#define	ENCODER_UART_TX_BUF_SIZE	512
uint8_t	ENCODER_uart_rx_buffer[ENCODER_UART_RX_BUF_SIZE];
uint8_t	ENCODER_uart_tx_buffer[ENCODER_UART_TX_BUF_SIZE];

UART_DriverStruct_t ENCODER_Uart_Drv =
{
	.data = ENCODER_uart_rx_buffer,
	.rx_max_len = ENCODER_UART_RX_BUF_SIZE,
	.uart = &huart1,
	.wakeup_id = WAKEUP_FROM_UART1_IRQ,
	.timeout = 100,
	.flags = UART_USES_DMA_TX | UART_USES_DMA_RX | UART_WAKEUP_ON_RXFULL | UART_WAKEUP_ON_TIMEOUT,
};

#define	HEATER_CHANNEL	TIM_CHANNEL_4
#define	LAMP_CHANNEL	TIM_CHANNEL_1
#define	AUX_CHANNEL		TIM_CHANNEL_2

#define	PWM_TIMER_MAX		5000
#define	PWM_TIMER_MIN		0
#define	PWM_TIMER_STEP		500

Pwm_Control_DriverStruct_t	Heater_Pwm_Control =
{
		.timer = &htim4,
		.pulse_width = {0,0,0,1,0,0},
};

Pwm_Control_DriverStruct_t	Lamp_Aux_Pwm_Control =
{
		.timer = &htim3,
		.pulse_width = {1,1,0,0,0,0},
};

void process_1_init(uint32_t process_id)
{

}


void process_1(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	heater_pwm=0,lamp_pwm=2000,aux_pwm=4000;
uint32_t	heater_up=1,lamp_up=1,aux_up=1;

	uart_register(&BT_Uart_Drv);
	uart_register(&ENCODER_Uart_Drv);
	uart_start_receive(&BT_Uart_Drv);
	uart_start_receive(&ENCODER_Uart_Drv);
	pwm_register(&Heater_Pwm_Control);
	pwm_register(&Lamp_Aux_Pwm_Control);
	pwm_init(&Heater_Pwm_Control);
	pwm_init(&Lamp_Aux_Pwm_Control);
	pwm_start_all_enabled(&Heater_Pwm_Control);
	pwm_start_all_enabled(&Lamp_Aux_Pwm_Control);

	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);

	while(1)
	{
		wait_event(EVENT_TIMER);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			process_led();
			if ( heater_up )
			{
				heater_pwm += PWM_TIMER_STEP;
				if ( heater_pwm >= PWM_TIMER_MAX )
					heater_up = 0;
			}
			else
			{
				heater_pwm -= PWM_TIMER_STEP;
				if ( heater_pwm == PWM_TIMER_MIN )
					heater_up = 1;
			}
			if ( lamp_up )
			{
				lamp_pwm += PWM_TIMER_STEP;
				if ( lamp_pwm >= PWM_TIMER_MAX )
					lamp_up = 0;
			}
			else
			{
				lamp_pwm -= PWM_TIMER_STEP;
				if ( lamp_pwm == PWM_TIMER_MIN )
					lamp_up = 1;
			}
			if ( aux_up )
			{
				aux_pwm += PWM_TIMER_STEP;
				if ( aux_pwm >= PWM_TIMER_MAX )
					aux_up = 0;
			}
			else
			{
				aux_pwm -= PWM_TIMER_STEP;
				if ( aux_pwm == PWM_TIMER_MIN )
					aux_up = 1;
			}
			pwm_set_width(&Heater_Pwm_Control, heater_pwm,HEATER_CHANNEL);
			pwm_set_width(&Lamp_Aux_Pwm_Control, lamp_pwm  ,LAMP_CHANNEL);
			pwm_set_width(&Lamp_Aux_Pwm_Control, aux_pwm,AUX_CHANNEL);

		}
	}
}
#endif //#ifndef SAMPLE_PROCESSES_ENABLED

