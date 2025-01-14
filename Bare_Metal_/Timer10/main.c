
#include "arm.h"

void rcc_config(void);
void gpio_moder(void);
void peripheral_bus(void);
void led_blinking(void);
void delay(void);


int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();
	while(1)
	{
		led_blinking();
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

/*void ms (int ms)
{
	for(int i=0;i< ms *4000; i++)
	{
		__asm("NOP");
	}
}*/
void led_blinking()
{
	if (GPIOA->ODR & (1 << 5))
	{
		GPIOA->ODR &= ~(1<<5); // PORTA LED ON
		delay(); // TIMER10
	}
	else
	{
		GPIOA->ODR |= (1<<5);
		delay();
	}
}

void delay(void)
{
	//Enable Update disable
	TIM10->CR1 = TIM10->CR1 | (1<<1);

	//clear UIF status
	TIM10->SR = TIM10->SR * ~(1<<0);

	//Set count value
	TIM10->CNT = 0;

	//Set prescaler value
	TIM10->PSC = 1600;

	//Set reload value
	TIM10->ARR = 1000;

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
