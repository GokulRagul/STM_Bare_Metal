/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :30/dec/2024                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :External_iterrupt_port B0                            */
/***********************************************************************/

// External_interrput_port_b0

// rcc_config

volatile unsigned int *RCC_CR = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;
volatile unsigned int *RCC_APB2ENR = (volatile unsigned int *)0x40023844;

//port config

volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;
volatile unsigned int *GPIOB_ODR = (volatile unsigned int *)0x40020414;
volatile unsigned int *GPIOB_PUPDR = (volatile unsigned int *)0x4002040c;

//External_config

volatile unsigned int *EXTI_IMR = (volatile unsigned int *)0x40013c00;
volatile unsigned int *EXTI_RTSR = (volatile unsigned int *)0x40013c08;
volatile unsigned int *EXTI_PR = (volatile unsigned int *)0x40013c14;

volatile unsigned int *SYSCFG_EXTICR1 = (volatile unsigned int *)0x40013808;
volatile unsigned int *NVIC_ISER0 = (volatile unsigned int *)0xE000E100;


void rcc_config(void);
void peripheral_bus(void);
void gpio_moder(void);
void delay_ms(int ms);
void exti_config(void);
void EXTIO_IRQHandler(void);

int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();
	exti_config();

	while(1)
	{
		*GPIOB_ODR  = *GPIOB_ODR | (1 << 1); // LED ON
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
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 1); //I/O PORT ENABLE
	*RCC_APB2ENR = *RCC_APB2ENR | (1 << 14); // SET SYSCONFIG ENABLE
}

void gpio_moder()
{
	*GPIOB_MODER = (*GPIOB_MODER & ~(0X3 << 2)) | (2 << 1); // OUTPUT MODE

	//SET PULL_UP and pull down

	//*GPIOA_PUPDR  = (*GPIOA_PUPDR  & ~(0X3 << 1)) | (1 << 0); // PULL UP

	*GPIOB_PUPDR = (*GPIOB_PUPDR  & ~(0X3 << 0)) | (2 << 0); // PULL_DOWN
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

	//*SYSCFG_EXTICR1 &= ~(0XF << 0); // CLEAR BIT 3:0 FOR EXTI0
	//*SYSCFG_EXTICR1 &= ~(0X0 << 0); // SET EXTIO TO MAP TO PA0;
	*SYSCFG_EXTICR1 = (*SYSCFG_EXTICR1 & ~(0XF << 0)) | (1 << 0	); // PBO->EXTI0

	//ENABLE INTERRUPT MASK
	*EXTI_IMR |= (1 << 0);

	//ENABLE RISING EDGE TRIGGER ON EXTI0
	*EXTI_RTSR  |= (1 << 0);

	//ENABLE NVIC FOR EXTIO_TRQ6 IN NVIC ISER0

	*NVIC_ISER0 |= (1 << 6);
}

void EXTI0_IRQHandler()
{
	if (*EXTI_PR & (1 << 0 ))
	{
		for(int i=0;i<5;i++)
		{
			*GPIOB_ODR &= ~(1 << 1); //LED TURN OFF
			delay_ms(100);
			*GPIOB_ODR |= (1 << 1); // KEEP ON LED BLINKING
			delay_ms(100);
		}
		//LED_MODE ^= 1; 	 // TOGGLE LED MODE
		*EXTI_PR |= (1 << 0	); // CLEAR THE INTERRUPT PENDING BIT
		}
}
