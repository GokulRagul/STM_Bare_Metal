/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :22/dec/2024                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :systick_timer_35ms                                   */
/***********************************************************************/

// systick_timer_35ms

//rcc register 

volatile unsigned int *RCC_CR = (volatile unsigned int *)0x40023800; //clock control register
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;//clock configuration register
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;//peripheral clock enable register

//gpio rgister 

volatile unsigned int *GPIOC_MODER = (volatile unsigned int *)0x40020800;//GPIO_PORTC register
volatile unsigned int *GPIOC_ODR   = (volatile unsigned int *)0x40020814;//OUTPUT DATA REGISTER PORTA
volatile unsigned int *STK_CTRL  = (volatile unsigned int *)0xE000E010;//SYSTICK_CONTROL_REGISTER
volatile unsigned int *STK_LOAD  = (volatile unsigned int *)0xE000E014;//SYSTICK_LOAD_REGISTER



void rcc_config(void);
void peripheral_bus_config(void);
void gpioc_moder_config(void);
void led_blinking(void);
void systick_timer_delay(int );



int main(void)
{

	rcc_config();
	peripheral_bus_config();
	gpioc_moder_config();
	while(1)
	{
		led_blinking();
	}
}

void rcc_config(void)
{
	//CONTROL REGISTER

		/* *rcc_cr page no: 103 */

	*RCC_CR = *RCC_CR & (~0x00010000);//HESON clock disable

	*RCC_CR |= (1 << 16);// HESON clock enable

	/* default internal clock */

        //CLOCK CONFIGURATION

	    /*  *rcc_cfgr Page no: 107 */

	*RCC_CFGR &= ~(0x00000003);

	*RCC_CFGR |= (1 << 0);

	while(!(*RCC_CFGR & 1 << 2));

}

void peripheral_bus_config(void)
{
        //ADVANCED HIGH-SPEED BUS1 ENABLE

	//  *rcc_ahb1enr page no: 118 
	*RCC_AHB1ENR |= (1 << 2);// peripheral clock enable in port a
}

void gpioc_moder_config(void)
{
	*GPIOC_MODER |= (1 << 26);
}

void systick_timer_delay(int val)
{
    *STK_LOAD &= ~(0xFFFFFF);
    
    // add reload value LOAD 
    
    *STK_LOAD |= val;

     //configure control register CTRL 
 
    *STK_CTRL |= (5 << 0);

    /* wait for count down complete */
    
    while(!(*STK_CTRL & (1 << 16)));

    *STK_CTRL &= (~1 << 16);
}

void led_blinking(void)
{
	*GPIOC_ODR &= (~ 1 << 13);
	   systick_timer_delay(560000); // count value 35ms

	 *GPIOC_ODR |= (1 << 13);
	   systick_timer_delay(560000); // count value 35ms

}
