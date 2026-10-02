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
 * ov.h
 *
 *  Created on: Sep 15, 2026
 *      Author: fil
 */

#ifndef OV_H_
#define OV_H_

extern	UART_HandleTypeDef huart1;
extern	UART_HandleTypeDef huart3;
extern	TIM_HandleTypeDef htim2;
extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim4;
extern	TIM_HandleTypeDef htim15;
extern	ADC_HandleTypeDef hadc1;
extern	I2C_HandleTypeDef hi2c1;
extern	DMA_HandleTypeDef hdma_tim2_ch4;

extern	void process_led(void);

#endif /* OV_H_ */
