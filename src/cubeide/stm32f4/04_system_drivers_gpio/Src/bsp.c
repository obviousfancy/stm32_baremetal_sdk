/*
 * bsp.c
 *
 *  Created on: Aug 2, 2026
 *      Author: obviousfancy
 */

#include "bsp.h"

#define BIT(n)   (1U << (n))

#define GPIOAEN			BIT(0)
#define GPIOCEN			BIT(2)
#define PIN5_ON			BIT(5)
#define PIN5_OFF		BIT(21)
#define LED_PIN_ON		PIN5_ON
#define LED_PIN_OFF		PIN5_OFF

#define PIN13			BIT(13)
#define BTN_PIN			PIN13

void led_init(void){
	/*Enable Clock Access to GPIOA*/
	RCC->AHB1ENR	|= GPIOAEN;

	/*Set PA5 mode to output mode*/
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~ (1U << 11);

}

void led_on(void){
	/*Set PA5 high*/
	//GPIOA->ODR |= LED_PIN;
	GPIOA->BSRR	|= LED_PIN_ON;
}

void led_off(void){
	/*Set PA5 low*/
	//GPIOA->ODR &=~ LED_PIN;
	GPIOA->BSRR	|= LED_PIN_OFF;
}

void button_init(void){
	/*Enable Clock Access to PORTC*/
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PC13 as an input pin*/
	GPIOC->MODER &=~ (1U << 26);
	GPIOA->MODER &=~ (1U << 27);
}

bool get_btn_state(void){

	/*Check if button is pressed*/
	if(GPIOC->IDR & BTN_PIN)
	{
		return false;
	}else{
		return true;
	}

}
