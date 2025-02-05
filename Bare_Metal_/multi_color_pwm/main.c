#include "arm.h"

void rcc_config(void);
void gpio_moder(void);
void peripheral_bus(void);
void delay_ms(int arr);
void red(void);
void blue(void);
void green(void);
void cyan(void);
void magenta(void);
void yellow(void);
void white(void);

int main()
{
    rcc_config();
    peripheral_bus();
    gpio_moder();

    while (1)
    {
    	red();
    	delay_ms(1500);
    	blue();
    	delay_ms(1500);
    	green();
    	delay_ms(1500);
        cyan();
        delay_ms(1500);
        magenta();
        delay_ms(1500);
        yellow();
        delay_ms(1500);
        white();
        delay_ms(1500);
    }
}

void rcc_config()
{
	//CONTROL REGISTER

	//RCC_CR PAGE NO :103

	RCC->CR  = RCC->CR & (~(1 << 16)); //HESON CLOCK DISABLE
	RCC->CR  = RCC->CR | (1 << 16); //HESON CLOCK ENABLE

	while (!(RCC->CR & (1 << 17)));

	// 	CLOCK CONFIG

	RCC->CFGR = RCC->CFGR  & (~(3 << 1));//clear system clock switch
	RCC->CFGR = RCC->CFGR  | (1 << 0); //HSC selected as system clock

	while (!(RCC->CFGR & (1 << 2))); //HSC oscillator used as system clock
}

void peripheral_bus()
{
    RCC->AHB1ENR = RCC->AHB1ENR | (1 << 0);//IO PORTA clock enable 
    RCC->APB2ENR |= (1 << 17);  // Enable TIM10 Clock
}

// Configure GPIOA (PA5, PA6, PA7) as Output
void gpio_moder()
{
    GPIOA->MODER &= ~(0x3 << 10);
    GPIOA->MODER |= (1 << 10);  // PA5 Output (Red)

    GPIOA->MODER &= ~(0x3 << 12);
    GPIOA->MODER |= (1 << 12);  // PA6 Output (Green)

    GPIOA->MODER &= ~(0x3 << 14);
    GPIOA->MODER |= (1 << 14);  // PA7 Output (Blue)
}

// red (red)
void red()
{
    GPIOA->ODR |= (1 << 5); // Red ON
    GPIOA->ODR &= ~(1 << 6);  // Green OFF
    GPIOA->ODR &= ~(1 << 7);  // Blue OFF
}
// blue (blue)
void blue()
{
    GPIOA->ODR &= ~(1 << 5); // Red OFF
    GPIOA->ODR &= ~(1 << 6);  // Green OFF
    GPIOA->ODR |= (1 << 7);  // Blue ON
}
// green (green)
void green()
{
    GPIOA->ODR &= ~(1 << 5); // Red OFF
    GPIOA->ODR |= (1 << 6);  // Green ON
    GPIOA->ODR &= ~(1 << 7);  // Blue OFF
}
// Cyan (Green + Blue)
void cyan()
{
    GPIOA->ODR &= ~(1 << 5); // Red OFF
    GPIOA->ODR |= (1 << 6);  // Green ON
    GPIOA->ODR |= (1 << 7);  // Blue ON
}

// Magenta (Red + Blue)
void magenta()
{
    GPIOA->ODR |= (1 << 5);  // Red ON
    GPIOA->ODR &= ~(1 << 6); // Green OFF
    GPIOA->ODR |= (1 << 7);  // Blue ON
}

// Yellow (Red + Green)
void yellow()
{
    GPIOA->ODR |= (1 << 5);  // Red ON
    GPIOA->ODR |= (1 << 6);  // Green ON
    GPIOA->ODR &= ~(1 << 7); // Blue OFF
}

// White (Red + Green + Blue)
void white()
{
    GPIOA->ODR |= (1 << 5);  // Red ON
    GPIOA->ODR |= (1 << 6);  // Green ON
    GPIOA->ODR |= (1 << 7);  // Blue ON
}

// Timer10 Based Delay
void delay_ms(int arr)
{
    TIM10->CR1 |= (1 << 1);  // Update disable
    TIM10->SR &= ~(1 << 0);  // Clear UIF
    TIM10->CNT = 0;
    TIM10->PSC = 999;  // Prescaler (16MHz / 16000 = 1kHz)
    TIM10->ARR = arr;     // Set delay count
    TIM10->CR1 &= ~(1 << 1); // Update disable OFF
    TIM10->CR1 |= (1 << 7);  // Update request source
    TIM10->CR1 |= (1 << 2);  // Auto-reload enable
    TIM10->CR1 |= 1;         // Enable Timer

    while ((TIM10->SR & 1) == 0);  // Wait for update flag
}
