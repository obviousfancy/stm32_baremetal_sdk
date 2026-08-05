/**
 * @file      ofl_rcc.c
 * @brief     
 *
 * @details   
 *
 * @author    obviousfancy
 * @date      Aug 4, 2026
 * @version   0.0.1
 *
 * @note      
 *
 * @copyright Copyright (c) 2026 ObviousFancy Lab
 *            Licensed under the MIT License
 */

#include "ofl_rcc.h"


void ofl_rcc_hse_config(void){
	/*
	 *	Settings Parameters	-->		STM32F103 Clock Tree
	 *
	 *	HSE = 8 MHz
	 *	PLL_M = 9
	 *	USB Divider = 1.5
	 *	AHB Preescaler = 1
	 *	Cortex Preescaler = 1
	 *	--> 72 MHz System Clock
	 *
	 *	APB1 Preescaler = 2	-->	36,72 MHz
	 *	APB2 Preescaler = 1	-->	72 MHz
	 *	ADC Preescaler	= 6	-->	12 MHz
	 */

	//PLL Configuration

	//PLL_M = 9
		//RCC->CFGR	&=~ (0xFUL	<< 18);			//Clear bitfields	[21:18]			111111111110000111111111111111111
	RCC->CFGR	&=~ (RCC_CFGR_PLLMULL);

	RCC->CFGR	|=	(7UL << 18);				//Configurable via struct

	//USB Preescaler = 1.5
	RCC->CFGR	&= ~(RCC_CFGR_USBPRE);			//Clear bitfield [22]

	/*HSE Oscillator*/
	//Enable HSE Oscillator
	RCC->CR	|= (RCC_CR_HSEON);
	//Wait for stabilize
	while((RCC->CR	& RCC_CR_HSERDY) == 0);
	//Select HSE as PLL Source
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	//Enable PLL
	RCC->CR |= RCC_CR_PLLON;
	//wait for PLL Ready
	while((RCC->CR	& RCC_CR_PLLRDY) == 0);

	//Flash Prefetch and wait state
	//2Wait States = 72 MHz
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);			//Clear Latency Fields
	FLASH->ACR |= FLASH_ACR_LATENCY_1;
	//Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	//Select PLL and main system clock
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_1;
	//Wait for PLL to be active clk source
	while((RCC->CFGR	&	RCC_CFGR_SWS_1) == 0);

	//Peripherals clock setup
	//AHB Clock Preescaler
	RCC->CFGR	&= ~(RCC_CFGR_HPRE);			//Clear
	//APB1 Preescaler
	RCC->CFGR	&= ~(RCC_CFGR_PPRE1);
	RCC->CFGR	|=	(RCC_CFGR_PPRE1_2);
	//APB2 Preescaler
	RCC->CFGR	&= ~(RCC_CFGR_PPRE2);			///Clear
	//ADC__Preescaler
	RCC->CFGR	&= ~(RCC_CFGR_ADCPRE);			//Clear
	RCC->CFGR	|=	(RCC_CFGR_ADCPRE_1);


}
