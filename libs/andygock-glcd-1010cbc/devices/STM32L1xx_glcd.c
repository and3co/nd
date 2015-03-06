/**
	\file STM32F0xx.c
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

#if defined(GLCD_DEVICE_STM32L1XX)

/* Includes from CMSIS and Peripheral Library */
//#include "stm32f0xx.h"
//#include "stm32f0xx_gpio.h"
//#include "stm32f0xx_spi.h"
//#include "stm32f0xx_rcc.h"
//#include "stm32f0xx_misc.h"
#include "stm32l1xx_hal.h"

/* Includes from GLCD */
#include "../glcd.h"
#include "inc/STM32L1xx_glcd.h"
SPI_HandleTypeDef  SPI_Handle;

void glcd_init(void)
{

#if defined(GLCD_CONTROLLER_PCD8544)
	/* Initialisation for PCD8544 controller */

	/* Declare GPIO and SPI init structures */
	GPIO_InitTypeDef GPIO_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Need to make start up the correct peripheral clocks */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		
	/* SS pin */
	CONTROLLER_SPI_SS_CLK_ENA();
	GPIO_InitStructure.Pin   = CONTROLLER_SPI_SS_PIN;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(CONTROLLER_SPI_SS_PORT, &GPIO_InitStructure);
	
	/* DC pin */
	CONTROLLER_SPI_DC_CLK_ENA();
	GPIO_InitStructure.Pin = CONTROLLER_SPI_DC_PIN;
	HAL_GPIO_Init(CONTROLLER_SPI_DC_PORT, &GPIO_InitStructure);

	/* RESET pin */
	CONTROLLER_SPI_RST_CLK_ENA();
	GPIO_InitStructure.Pin = CONTROLLER_SPI_RST_PIN;
	HAL_GPIO_Init(CONTROLLER_SPI_RST_PORT, &GPIO_InitStructure);

	/* Make sure chip is de-selected by default */
	GLCD_DESELECT();

	SPI_Handle.Instance = CONTROLLER_SPI_NUMBER;

	/* Initialise SPI */
	SPI_Handle.Init.Direction         = SPI_DIRECTION_2LINES;
	SPI_Handle.Init.Mode              = SPI_MODE_MASTER;
	SPI_Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
	SPI_Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	SPI_Handle.Init.CLKPhase          = SPI_PHASE_2EDGE;
	SPI_Handle.Init.NSS               = SPI_NSS_SOFT;
	SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; /* Set clock speed! */
	SPI_Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SPI_Handle.Init.CRCPolynomial     = 7;
	HAL_SPI_Init(&SPI_Handle);

	/* Enable SPI interupts */
	/*
	SPI_I2S_ITConfig(CONTROLLER_SPI_NUMBER, SPI_I2S_IT_TXE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_Init(&NVIC_InitStructure);
	*/
	
	/* Initialisation sequence of controller */
	glcd_reset();

	/* Get into the EXTENDED mode! */
	glcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);

	/* LCD bias select (4 is optimal?) */
	glcd_command(PCD8544_SET_BIAS | 0x2);

	/* Set VOP */
	glcd_command(PCD8544_SET_VOP | 50); // Experimentally determined

	/* Back to standard instructions */
	glcd_command(PCD8544_FUNCTION_SET);

	/* Normal mode */
	glcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);

	glcd_select_screen((uint8_t *)&glcd_buffer,&glcd_bbox);

	glcd_set_contrast(50);

	glcd_clear();


#else
	#error "Controller not supported by STM32F0xx"
#endif

}

void glcd_spi_write(uint8_t c)
{

	GLCD_SELECT();
	HAL_SPI_Transmit(&SPI_Handle, &c, sizeof(c), 400);
	
	/* Wait until entire byte has been read (which we discard anyway) */
	//while(SPI_I2S_GetFlagStatus(CONTROLLER_SPI_NUMBER, SPI_I2S_FLAG_BSY) != RESET);

	GLCD_DESELECT();
}

void glcd_reset(void)
{
	/* Toggle RST low to reset. Minimum pulse 100ns on datasheet. */
	GLCD_SELECT();
	GLCD_RESET_LOW();
	delay_ms(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}

#endif
