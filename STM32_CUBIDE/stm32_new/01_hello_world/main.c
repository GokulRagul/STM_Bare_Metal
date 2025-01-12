#include "arm.h"

// Function Prototypes
void rcc_config(void);
void peripheral_bus(void);
void gpioc_moder(void);
void delay_ms(int ms);
void led_blinking(void);

int main()
{
    rcc_config();           // Configure RCC
    peripheral_bus();       // Enable peripheral clock for GPIOC
    gpioc_moder();          // Configure PC13 as output

    while (1)
    {
        led_blinking();      // Blink the LED
    }
}

void rcc_config()
{
    RCC->CR &= ~0x00010000; // Disable HSE (High-Speed External Oscillator)
    RCC->CR |= (1 << 16);   // Enable HSE

    while (!(RCC->CR & (1 << 17))); // Wait for HSE to be ready

    RCC->CFGR &= ~0x00000003; // Clear system clock selection
    RCC->CFGR |= (1 << 0);    // Select HSE as the system clock

    while (!(RCC->CFGR & (1 << 2))); // Wait for HSE to be the system clock
}

void peripheral_bus()
{
    RCC->AHB1ENR |= (1 << 2); // Enable clock for GPIOC (Port C)
}

void gpioc_moder()
{
    // Configure PC13 as output (MODER[27:26] = 01)
    GPIOC->MODER = (GPIOC->MODER & ~(3 << 26)) | (1 << 26); // Set PC13 as output mode
}

void delay_ms(int ms)
{
    // Simple delay loop (approximation based on the clock speed)
    for (int i = 0; i < ms * 4000; i++)
    {
        __asm("NOP"); // No operation - delay
    }
}

void led_blinking()
{
    // Check if the LED (PC13) is ON
    if (GPIOC->ODR & (1 << 13))
    {
        GPIOC->ODR &= ~(1 << 13);  // Clear bit to turn LED OFF
        delay_ms(1000);            // 1-second delay
    }
    else
    {
        GPIOC->ODR |= (1 << 13);   // Set bit to turn LED ON
        delay_ms(100);             // 0.1-second delay
    }
}
