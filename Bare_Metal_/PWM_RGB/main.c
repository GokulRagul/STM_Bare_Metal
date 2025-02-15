/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :15/FEB/2025                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :PWM_RGB                                              */
/***********************************************************************/

#include "arm.h"

void rcc_config(void);
void gpio_moder(void);
void timer1_pwm_init(void);

int main()
{
    rcc_config();
    gpio_moder();
    timer1_pwm_init();

    while (1)
    {
    	// meginta color
        for(int i = 0; i < 199; i++)
        {
            while (!(TIM1->SR & (1 << 0)));  // Wait for update flag
            TIM1->SR &= ~(1 << 0);  // Clear flag
            TIM1->CCR1 = 199;  // Adjust duty cycle for CH1
            TIM1->CCR2 = 0; // Adjust duty cycle for CH2
            TIM1->CCR3 = 199;  // Adjust duty cycle for CH3
        }
        // cyan color
        for(int j = 199; j > 0; j--)
        {
            while (!(TIM1->SR & (1 << 0)));
            TIM1->SR &= ~(1 << 0);
            TIM1->CCR1 = 0;
            TIM1->CCR2 = 199;
            TIM1->CCR3 = 199;
        }
         // lite green
        for(int i = 0; i < 199; i++)
        {
            while (!(TIM1->SR & (1 << 0)));  // Wait for update flag
            TIM1->SR &= ~(1 << 0);  // Clear flag
            TIM1->CCR1 = 40;  // Adjust duty cycle for CH1
            TIM1->CCR2 = 159; // Adjust duty cycle for CH2
            TIM1->CCR3 = 0;  // Adjust duty cycle for CH3
        }
         //  brown
        for(int j = 199; j > 0; j--)
        {
            while (!(TIM1->SR & (1 << 0)));
            TIM1->SR &= ~(1 << 0);
            TIM1->CCR1 = 40;
            TIM1->CCR2 = 40;
            TIM1->CCR3 = 0	;
        }
    }
}

// Enable TIM1 and GPIOA Clocks
void rcc_config()
{
    RCC->CR |= (1 << 0);  // Enable HSE
    while (!(RCC->CR & (1 << 1)));  // Wait for HSE ready

    RCC->CFGR &= ~(3 << 0);
    while ((RCC->CFGR & (3 << 2)) != (0 << 2)); // Wait for HSE to be system clock

    RCC->AHB1ENR |= (1 << 0);  // Enable GPIOA Clock
    RCC->APB2ENR |= (1 << 0);  // Enable TIM1 Clock
}

// Configure PA8, PA9, PA10 as Alternate Function TIM1
void gpio_moder()
{
    GPIOA->MODER |= (2 << (8 * 2));  // PA8 in Alternate Function Mode
    GPIOA->MODER |= (2 << (9 * 2));  // PA9 in Alternate Function Mode
    GPIOA->MODER |= (2 << (10 * 2)); // PA10 in Alternate Function Mode

    GPIOA->AFRH |= (1 << (0 * 4));  // PA8 AF1 (TIM1_CH1)
    GPIOA->AFRH |= (1 << (1 * 4));  // PA9 AF1 (TIM1_CH2)
    GPIOA->AFRH |= (1 << (2 * 4));  // PA10 AF1 (TIM1_CH3)
}

// Configure TIM1 with 3 PWM Channels
void timer1_pwm_init()
{
    TIM1->PSC = 1000;  // Prescaler (84MHz / (PSC+1) = 10KHz)
    TIM1->ARR = 199;  // Auto-reload (199+1) * 0.1ms = 20ms period

    // Configure TIM1 Channel 1, 2, and 3 in PWM Mode 1
    TIM1->CCMR1 |= (6 << 4);  // PWM Mode 1 on CH1
    TIM1->CCMR1 |= (6 << 12); // PWM Mode 1 on CH2
    TIM1->CCMR2 |= (6 << 4);  // PWM Mode 1 on CH3

    TIM1->CCMR1 |= (1 << 3); // Enable preload for CH1
    TIM1->CCMR1 |= (1 << 11); // Enable preload for CH2
    TIM1->CCMR2 |= (1 << 3); // Enable preload for CH3

    TIM1->CCER |= (1 << 0);  // Enable Capture/Compare CH1
    TIM1->CCER |= (1 << 4);  // Enable Capture/Compare CH2
    TIM1->CCER |= (1 << 8);  // Enable Capture/Compare CH3

    TIM1->EGR |= (1 << 0); // Force update event
    TIM1->BDTR |= (1 << 15); // Enable Main Output (MOE for TIM1)
    TIM1->CR1 |= (1 << 7);   // Enable Auto-reload Preload (ARPE)
    TIM1->CR1 |= (1 << 0);   // Enable Counter (CEN)

}
