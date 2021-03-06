/**
  ******************************************************************************
  * @file    Templates/Src/stm32l1xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "STM32L1xx_glcd.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is generated automatically by MicroXplorer and eventually  
            modified by the user
   */ 
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  /* NOTE : This function is generated automatically by MicroXplorer and eventually  
            modified by the user
   */
}

/**
  * @brief  Initializes the PPP MSP.
  * @param  None
  * @retval None
  */
/*void HAL_PPP_MspInit(void)
{*/
  /* NOTE : This function is generated automatically by MicroXplorer and eventually  
            modified by the user
   */ 
/*}*/

/**
  * @brief  DeInitializes the PPP MSP.
  * @param  None  
  * @retval None
  */
/*void HAL_PPP_MspDeInit(void)
{*/
  /* NOTE : This function is generated automatically by MicroXplorer and eventually  
            modified by the user
   */
/*}*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi){

	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	CONTROLLER_SPI_SCK_CLK_ENA();
	CONTROLLER_SPI_MISO_CLK_ENA();
	CONTROLLER_SPI_MOSI_CLK_ENA();
	/* Enable SPI clock */
	CONTROLLER_SPI_CLK_ENA();

	/*##-2- Configure peripheral GPIO ##########################################*/  
	/* SPI SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin       = CONTROLLER_SPI_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = CONTROLLER_SPI_SCK_AF;
	HAL_GPIO_Init(CONTROLLER_SPI_SCK_PORT, &GPIO_InitStruct);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = CONTROLLER_SPI_MISO_PIN;
	GPIO_InitStruct.Alternate = CONTROLLER_SPI_MISO_AF;
	HAL_GPIO_Init(CONTROLLER_SPI_MISO_PORT, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = CONTROLLER_SPI_MOSI_PIN;
	GPIO_InitStruct.Alternate = CONTROLLER_SPI_MOSI_AF;
	HAL_GPIO_Init(CONTROLLER_SPI_MOSI_PORT, &GPIO_InitStruct);
}

/**
  * @brief SPI MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to its default state
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	/*##-1- Reset peripherals ##################################################*/
	__SPI1_FORCE_RESET();
	__SPI1_RELEASE_RESET();
	
	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* Configure SPI SCK as alternate function  */
	HAL_GPIO_DeInit(CONTROLLER_SPI_SCK_PORT, CONTROLLER_SPI_SCK_PIN);
	/* Configure SPI MISO as alternate function  */
	HAL_GPIO_DeInit(CONTROLLER_SPI_MISO_PORT, CONTROLLER_SPI_MISO_PIN);
	/* Configure SPI MOSI as alternate function  */
	HAL_GPIO_DeInit(CONTROLLER_SPI_MOSI_PORT, CONTROLLER_SPI_MOSI_PIN);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
