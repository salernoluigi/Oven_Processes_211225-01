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
 * process_2.c
 *
 *  Created on: Jan 10, 2025
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"
#ifndef SAMPLE_PROCESSES_ENABLED
#include "ov.h"

uint16_t ws2812_work_buf[WS2812_DMA_BUF_SIZE];
LED_Frame_Struct_t		LED_Frame[WS2812_NUM_LEDS];
WS2812_DriverStruct_t	WS2812_Drv =
{
	.wakeup_id 			 = WAKEUP_FROM_TIM_IRQ,
	.ws2812_timer        = &htim2,
	.hdma                = &hdma_tim2_ch4,
	.tim_instance        = TIM2,
	.dma_instance        = DMA1,
	.tim_channel         = TIM_CHANNEL_4,
	.tim_dma_cc_id       = TIM_DMA_CC4,
	.num_leds            = WS2812_NUM_LEDS,
	.dma_buf_size        = WS2812_DMA_BUF_SIZE,
	.dma_pwm_buffer      = ws2812_work_buf,
	.led_strip_data		 = LED_Frame,
	.brightness			 = 0x3f,
};

uint32_t ws_init_res=0;
void process_2_init(uint32_t process_id)
{
	ws_init_res=ws2812_register(&WS2812_Drv);
}


void process_2(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint32_t	ledlit=0,bright=0;
LED_Frame_Struct_t	pattern;

	pattern.R = 255;
	pattern.G = 0;
	pattern.B = 0;
	WS2812_Drv.brightness = 0;
	create_timer(TIMER_ID_0,20,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER);
		get_wakeup_flags(&wakeup,&flags);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			//if (WS2812_Drv.transmitting == 0 )
			{
				LED_Frame[(ledlit-1) & 0x07] = (LED_Frame_Struct_t){0, 0, 0}; // Clear last pixel
				LED_Frame[ledlit] = pattern; // Set first pixel Blue
				ws2812_Show_Frame(&WS2812_Drv);
				ledlit++;
				ledlit &= 0x07;
				if ( bright )
				{
					WS2812_Drv.brightness++;
					if( WS2812_Drv.brightness == 255 )
					{
						bright = 0;
					}
				}
				else
				{
					WS2812_Drv.brightness--;
					if( WS2812_Drv.brightness == 1 )
					{
						bright = 1;
						if ( pattern.R == 255 )
						{
							pattern.R = 0;
							pattern.G = 255;
							pattern.B = 0;
						}
						else if ( pattern.G == 255 )
						{
							pattern.R = 0;
							pattern.G = 0;
							pattern.B = 255;
						}
						else if ( pattern.B == 255 )
						{
							pattern.R = 255;
							pattern.G = 0;
							pattern.B = 0;
						}
					}
				}
			}
		}
	}
}
#endif //#ifndef SAMPLE_PROCESSES_ENABLED
