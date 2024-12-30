/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :22/dec/2024                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :GPIO_PORTA_8_LED_bin                                 */
/***********************************************************************/

// GPIO_PORTA_8_LED_bin

//RCC CONFIG

volatile unsigned int *RCC_CR = (volatile unsigned int *)0x40023800; //clock control register
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;//clock configuration register
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;//peripheral clock enable register

//PORT CONFIG

volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;//GPIO_PORTA register
volatile unsigned int *GPIOA_ODR = (volatile unsigned int *)0x40020014;//OUTPUT DATA REGISTER PORTA
//volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;
//volatile unsigned int *GPIOB_ODR = (volatile unsigned int *)0x40020414;

void rcc_config(void);
void gpioa_moder(void);
void peripheral_bus(void);
void led_blinking1(void);
void delay_ms(int ms);

// main function

int main ()
{
	rcc_config();
	peripheral_bus();
	gpioa_moder();

	while(1)
	{
		led_blinking1();

	}
}

void rcc_config()
{
	//CONTROL REGISTER

	/* *rcc_cr page no: 103 */

	*RCC_CR = *RCC_CR & (~(0b00000000000000010000000000000000)); //HESON clock disable

	*RCC_CR = *RCC_CR | (0b00000000000000010000000000000000); // HESON clock enable

	while (!(*RCC_CR & 0b00000000000000100000000000000000) == 0);

	//CLOCK CONFIGURATION

	/*  *rcc_cfgr Page no: 107 */

	*RCC_CFGR = *RCC_CFGR & (~(0b00000000000000000000000000000011)); //clear system clock

	*RCC_CFGR = *RCC_CFGR | (0b00000000000000000000000000000001);  //HSE Selected system  clock

	while (!(*RCC_CFGR & 0b00000000000000000000000000000100) == 4);
}

void peripheral_bus()
{
	//ADVANCED HIGH-SPEED BUS1 ENABLE

	/*  *rcc_ahb1enr page no: 118 */

	*RCC_AHB1ENR  = *RCC_AHB1ENR |(0b00000000000000000000000000000001); // peripheral clock enable in port a
  //	*RCC_AHB1ENR  = *RCC_AHB1ENR  |= (1 << 1); // peripheral clock enable in port b
}

void gpioa_moder()
{
	// GPIO_MODE_PORT A

	/* GPIO  PORT mpde register page no: 158 */
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000000000000001);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000000000000100);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000000000010000);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000000001000000);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000000100000000);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000000010000000000);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000001000000000000);
	*GPIOA_MODER = *GPIOA_MODER | (0b00000000000000000100000000000000);

	}
void delay_ms(int ms)
{
	for (int i = 0; i< ms * 4000; i++)
	{
		__asm("NOP");
	}
}

void led_blinking1()
{
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000000000001);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000000000010);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000000000100);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b0000000000000000000000000001000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000000010000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000000100000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000001000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR | (0b00000000000000000000000010000000);
	delay_ms(50);
	*GPIOA_ODR = *GPIOA_ODR & (0b00000000000000000000000000000000);
	delay_ms(50);

}
