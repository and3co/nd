/**
	\file STM32F0xx.h
	\author Andy Gock
	\brief Functions specific to STM32 F0 ARM Cortex-M0 devices.
 */

/*
	Copyright (c) 2012, Andy Gock

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of Andy Gock nor the
		  names of its contributors may be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL ANDY GOCK BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stm32l1xx_hal.h"

#ifndef STM32L1XX_H_
#define STM32L1XX_H_

#if defined(GLCD_DEVICE_STM32L1XX)

/** SPI port number e.g SPI1, SPI2 (not to be confused with GPIOA, GPIOB, etc) */
#define CONTROLLER_SPI_NUMBER      	SPI1
#define CONTROLLER_SPI_CLK_ENA()  	__SPI1_CLK_ENABLE()

#define CONTROLLER_SPI_SCK_CLK_ENA()	__GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_SCK_PORT    GPIOA
#define CONTROLLER_SPI_SCK_PIN     GPIO_PIN_5
#define CONTROLLER_SPI_SCK_AF	     GPIO_AF5_SPI1

#define CONTROLLER_SPI_MISO_CLK_ENA()  __GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_MISO_PORT   GPIOA
#define CONTROLLER_SPI_MISO_PIN    GPIO_PIN_6
#define CONTROLLER_SPI_MISO_AF	     GPIO_AF5_SPI1

#define CONTROLLER_SPI_MOSI_CLK_ENA()  __GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_MOSI_PORT   GPIOA
#define CONTROLLER_SPI_MOSI_PIN    GPIO_PIN_7
#define CONTROLLER_SPI_MOSI_AF	     GPIO_AF5_SPI1

#define CONTROLLER_SPI_SS_PORT  GPIOB
#define CONTROLLER_SPI_SS_CLK_ENA()  __GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_SS_PIN   GPIO_PIN_6

#define CONTROLLER_SPI_DC_PORT  GPIOC
#define CONTROLLER_SPI_DC_CLK_ENA()  __GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_DC_PIN   GPIO_PIN_7

#define CONTROLLER_SPI_RST_PORT GPIOA
#define CONTROLLER_SPI_RST_CLK_ENA()  __GPIOA_CLK_ENABLE()
#define CONTROLLER_SPI_RST_PIN  GPIO_PIN_9

#define GLCD_SELECT()     HAL_GPIO_WritePin(CONTROLLER_SPI_SS_PORT,CONTROLLER_SPI_SS_PIN,GPIO_PIN_RESET)
#define GLCD_DESELECT()   HAL_GPIO_WritePin(CONTROLLER_SPI_SS_PORT,CONTROLLER_SPI_SS_PIN,GPIO_PIN_SET)
#define GLCD_DC_LOW()     HAL_GPIO_WritePin(CONTROLLER_SPI_DC_PORT,CONTROLLER_SPI_DC_PIN,GPIO_PIN_RESET)
#define GLCD_DC_HIGH()    HAL_GPIO_WritePin(CONTROLLER_SPI_DC_PORT,CONTROLLER_SPI_DC_PIN,GPIO_PIN_SET)
#define GLCD_RESET_LOW()  HAL_GPIO_WritePin(CONTROLLER_SPI_RST_PORT,CONTROLLER_SPI_RST_PIN,GPIO_PIN_RESET)
#define GLCD_RESET_HIGH() HAL_GPIO_WritePin(CONTROLLER_SPI_RST_PORT,CONTROLLER_SPI_RST_PIN,GPIO_PIN_SET)

#else
	#error "Controller not supported by STM32F0XX"
#endif

#endif
