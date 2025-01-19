
#include "arm.h"

void rcc_config(void);
void gpio_moder(void);
void peripheral_bus(void);
void delay_ms(int arr);

int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();
	while(1)
	{

		/*GPIOA->ODR &= ~(1<<5);
		delay_ms(1000);
		GPIOA->ODR |= (1 << 5);
		delay_ms(500);*/


		for (int i=25;i<500;i+=9)
		{
			GPIOA->ODR &= ~(1 << 5);
			delay_ms(i);
			GPIOA->ODR |= (1 << 5);
			delay_ms(60);
		}
		for (int j=500;j>25;j-=9)
		{
			GPIOA->ODR &= ~(1 << 5);
			delay_ms(j);
			GPIOA->ODR |=(1 << 5);
			delay_ms(60);
		}
	}
}

void rcc_config()
{
	// clock selection
	RCC->CR |= 1<<16; //HSE ON

	while(!(RCC->CR & 1<<17));


	RCC->CFGR &= ~0x3; //HSE oscillator selected as system clock
	RCC->CFGR |= 1; //HSE oscillator selected as system clock

	while(!(RCC->CFGR & 0x1<<2)); //waiting for 01: HSE oscillator used as the system clock
}

void peripheral_bus()
{
	//Port A clock Selection
	RCC->AHB1ENR |= (1<<0);

	//timer10 selection
	RCC->APB2ENR |= 1<<17;
}

void gpio_moder()
{
	// port set as out put mode
	GPIOA->MODER &= ~0x3<<10;
	GPIOA->MODER |= 1<<10; // PORTA ENABLE
}


void delay_ms(int arr)
{
	//Enable Update disable
	TIM10->CR1 = TIM10->CR1 | (1<<1);

	//clear UIF status
	TIM10->SR = TIM10->SR * ~(1<<0);

	//Set count value
	TIM10->CNT = 0;

	//Set prescaler value
	TIM10->PSC = 999;

	//Set reload value
	TIM10->ARR = arr;
	//Update disable OFF
	TIM10->CR1 = TIM10->CR1 & ~(1<<1);

	//Update request source
	TIM10->CR1 = TIM10->CR1 | (1<<7);

	//Auto-reload preload enable
	TIM10->CR1 = TIM10->CR1 | (1<<2);

	//Counter enable
	TIM10->CR1 = TIM10->CR1 | 1;

	// condition

	while((TIM10->SR & 1)==0);
}


