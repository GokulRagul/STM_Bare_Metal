/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :22/dec/2024                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :PULL_UP_LED_INTERNAL                                 */
/***********************************************************************/

// pull up  led_internal

//rcc_config
volatile unsigned int  *RCC_CR = (volatile unsigned int *)0x40023800; //clock control register
volatile unsigned int  *RCC_CFGR = (volatile  unsigned int *)0x40023808;//clock configuration register
volatile unsigned int  *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;//peripheral clock enable register

//port config

volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;//GPIO_PORTA register
volatile unsigned int *GPIOA_ODR = (volatile unsigned int *)0x40020014;//OUTPUT DATA REGISTER PORTA
volatile unsigned int *GPIOA_PUPDR = (volatile unsigned int *)0x4002000c;//GPIO_PORTA  pullup pulldown register 
volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;//GPIO_PORTB register
volatile unsigned int *GPIOB_IDR = (volatile unsigned int *)0x40020410;//INPUT DATA REGISTER PORTA
volatile unsigned int *GPIOB_PUPDR = (volatile unsigned int *)0x4002040c;//GPIO_PORTB  pullup pulldown register 




void rcc_config(void);
void peripheral_bus(void);
void gpio_moder(void);
//void gpio_pupdr(void);
void delay_ms(int ms);
void led_blinking(void);

int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();
	//gpio_pupdr();

	while(1)
	{
		led_blinking();
	}
}

void rcc_config()
{
	//CONTROL REGISTER

	//RCC_CR PAGE NO :103

	*RCC_CR  = *RCC_CR & (~(1 << 16)); //HESON CLOCK DISABLE
	*RCC_CR  = *RCC_CR | (1 << 16); //HESON CLOCK ENABLE

	while (!(*RCC_CR & (1 << 17)));

	//CLOCK CONFIGURATION

	/*  *rcc_cfgr Page no: 107 */


	*RCC_CFGR = *RCC_CFGR  & (~(3 << 1));
	*RCC_CFGR = *RCC_CFGR  | (1 << 0);

	while (!(*RCC_CFGR & (1 << 2)));
}

void peripheral_bus()
{
        //ADVANCED HIGH-SPEED BUS1 ENABLE

	/*  *rcc_ahb1enr page no: 118 */
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 0);// peripheral clock enable in port a
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 1); // peripheral clock enable in portB
}

void delay_ms (int ms )
{
	for (int i=0;i<ms * 4000; i++)
	{
		__asm("NOP");
	}
}
void gpio_moder()
{
	*GPIOA_MODER = *GPIOA_MODER | (1 << 0);

    *GPIOB_MODER = *GPIOB_MODER & (~0x00000003);

    *GPIOB_PUPDR = *GPIOB_PUPDR | (1 << 1);

    //*GPIOA_MODER = *GPIOA_MODER  & (~0x00000006);
    //h*GPIOB_MODER = *GPIOB_MODER | (2 << 1 );

}

/*void gpio_pupdr()
{

	*GPIOB_PUPDR = *GPIOB_PUPDR | (2 << 1);
}*/

void led_blinking()
{
	if (*GPIOB_IDR  & (0x00000001))
	{
	  *GPIOA_ODR = *GPIOA_ODR | (1 << 0);
	}
	else
	{
		//*GPIOA_ODR = *GPIOA_ODR  | (1 << 0);
		*GPIOA_ODR = *GPIOA_ODR & (~1 << 0);
	}
}
