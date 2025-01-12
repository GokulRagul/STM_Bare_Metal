/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :03/jan/2025                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :External_iterrupt_portA_ FTSR                        */
/***********************************************************************/

// External_interrput_portA0_FTSR

// rcc_config

volatile unsigned int *RCC_CR = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;
volatile unsigned int *RCC_APB2ENR = (volatile unsigned int *)0x40023844;

//port config

volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR = (volatile unsigned int *)0x40020014;
volatile unsigned int *GPIOA_PUPDR = (volatile unsigned int *)0x4002000c;

//External_config

volatile unsigned int *EXTI_IMR = (volatile unsigned int *)0x40013c00;
volatile unsigned int *EXTI_FTSR = (volatile unsigned int *)0x40013c0c;
volatile unsigned int *EXTI_PR = (volatile unsigned int *)0x40013c14;

volatile unsigned int *SYSCFG_EXTICR1 = (volatile unsigned int *)0x40013808;
volatile unsigned int *NVIC_ISER0 = (volatile unsigned int *)0xE000E100;

void rcc_config(void);
void peripheral_bus(void);
void gpio_moder(void);
void delay_ms(int ms);
void exti_config(void);
void EXTI0_IRQHandler(void);

int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();
	exti_config();

	while (1)
	{
		*GPIOA_ODR  = *GPIOA_ODR | (1 << 5); // LED ON
	}
}

void rcc_config()
{
	*RCC_CR = *RCC_CR & (~(1 << 16)); //HSE CLOCK DISABLE
	*RCC_CR = *RCC_CR | (1 << 16); // HSE CLOCK ENABLE

	while (!(*RCC_CR & (1 << 17)));

	*RCC_CFGR = *RCC_CFGR & (~(3 << 1)); // CLEAR SYSTEM CLOCK
	*RCC_CFGR = *RCC_CFGR | (1 << 0); // HSE SELECTED SYSTEM CLOCK SWITCH

	while ((*RCC_CFGR & 0xc) != 0x4	);
}

void peripheral_bus()
{
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 0); //I/O PORTA

	*RCC_APB2ENR = *RCC_APB2ENR | (1 << 14); // SET SYSCONFIG ENABLE

}

void gpio_moder()
{
	*GPIOA_MODER = (*GPIOA_MODER & ~(0X3 << 10)) | (1 << 10); // OUTPUT MODE

	//SET PULL_UP and pull down

	*GPIOA_PUPDR  = (*GPIOA_PUPDR  & ~(0X3 << 1)) | (1 << 0); // PULL UP
}

void delay_ms(int ms)
{
	for(int i = 0; i < ms * 4000; i++)
	{
		__asm("NOP");
	}
}

void exti_config()
{

	*SYSCFG_EXTICR1 = (*SYSCFG_EXTICR1 & ~(0XF << 0)) | (0 << 0); // PA0->EXTI1

	//ENABLE INTERRUPT MASK
	*EXTI_IMR |= (1 << 0);

	//ENABLE INTERRUPT FALING TRIGGER
    *EXTI_FTSR |= (1 << 0);

	//ENABLE NVIC FOR EXTIO_TRQ6 IN NVIC ISER0

	*NVIC_ISER0  |= (1 << 6); // External interrupt Exti0

}
void EXTI0_IRQHandler()
{
	if (*EXTI_PR & (1 << 0 ))
	{
		for(int i=0;i<5;i++)
		{
			*GPIOA_ODR &= ~(1 << 5); //LED TURN OFF
			delay_ms(100);
			*GPIOA_ODR |= (1 << 5); // KEEP ON LED BLINKING
			delay_ms(100);
		}
		*EXTI_PR |= (1 << 0	); // CLEAR THE INTERRUPT PENDING BIT
		}
}
