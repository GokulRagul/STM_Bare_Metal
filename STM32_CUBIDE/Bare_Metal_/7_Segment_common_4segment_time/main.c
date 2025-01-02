/***********************************************************************/
/*Author         :Gokul S                                              */
/*Date           :22/dec/2024                                          */
/*File           :BARE_METAL_PROGRAM_STM32F401CCU6                     */
/*Description	 :7segment _common_cathode_4led                        */
/***********************************************************************/
//7_segment_common_cathode 4Led

// RCC_config

volatile unsigned int *RCC_CR = (volatile unsigned int *)0x40023800;  //clock control register
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808; //clock configuration register
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830; ////peripheral clock enable register

//port config

volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;  //GPIO_PORTA register
volatile unsigned int *GPIOA_ODR = (volatile unsigned int *)0x40020014;//OUTPUT DATA REGISTER PORTA
volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400; //GPIO_PORTA register
volatile unsigned int *GPIOB_ODR = (volatile unsigned int *)0x40020414;//OUTPUT DATA REGISTER PORTA

void rcc_config(void);
void peripheral_bus(void);
void gpio_moder(void);
void delay_ms(int ms);
void led_blinking(void);

int main()
{
	rcc_config();
	peripheral_bus();
	gpio_moder();


	while (1)
	{
		led_blinking();
	}
}

void rcc_config()
{
	//CONTROL REGISTER

		/* *rcc_cr page no: 103 */
	*RCC_CR = *RCC_CR & (~(1 << 16)); //HESON clock disable
	*RCC_CR = *RCC_CR | (1 << 16);// HESON clock enable

	while (!(*RCC_CR & (1<<17)));

	//CLOCK CONFIGURATION

		/*  *rcc_cfgr Page no: 107 */
	*RCC_CFGR = *RCC_CFGR & (~ (3 << 1)); //clear system clock
	*RCC_CFGR = *RCC_CFGR | (1 << 0);  //HSE Selected system  clock

	while (!(*RCC_CFGR  & (1 << 2 ) ));

}

void peripheral_bus()
{
	//ADVANCED HIGH-SPEED BUS1 ENABLE

		/*  *rcc_ahb1enr page no: 118 */
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 0);  // peripheral clock enable in portA
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 1);  // peripheral clock enable in portB
}

void gpio_moder ()
{
	int i, a = 0;
	for (i = 0; i<=9; i++)
	{
		*GPIOA_MODER  = *GPIOA_MODER  | (1 << a++);
		a++;
	}

		*GPIOB_MODER = *GPIOB_MODER | (1 << 0); // portB0
		*GPIOB_MODER = *GPIOB_MODER | (1 << 2); // portB1
		*GPIOB_MODER = *GPIOB_MODER | (1 << 4); // portB2
		*GPIOB_MODER = *GPIOB_MODER | (1 << 10); // portB5
}

void delay_ms(int ms)
{
	for (int i = 0; i< ms * 4000; i++)
	{
		__asm("NOP");
	}
}

void led_blinking()
{
	int i, led[10] = {0x0000003f, 0x00000006, 0x0000005b, 0x0000004f, 0x00000066, 0x0000006d, 0x0000007d, 0x00000007, 0x0000007f, 0x0000006f}; //0to9


	while(1)
	{
		for(i=0; i<6; i++)
		{
			for(int j=0;j<10;j++)
			{
			  for(int k=0;k<6;k++)
			  {
				 for(int l=0;l<10;l++)
				  {
					  for(int m=0;m<80;m++)
					  {
						*GPIOB_ODR =  0x00000001; // set PORTB0
						*GPIOB_ODR &= ~(1<<1); //clear portB1
						*GPIOB_ODR &= ~(1<<2); //clear portB2
						//*GPIOB_ODR &= ~(1<<5);
		         		*GPIOA_ODR = (led[i]);   //portA0-A6
						delay_ms(2);


						*GPIOB_ODR = 0x00000002; //  set PORTB0
						*GPIOB_ODR &= ~(1<<0); //clear portB1
						*GPIOB_ODR &= ~(1<<2); //clear portB2
						//*GPIOB_ODR &= ~(1<<5);
						*GPIOA_ODR = (led[j]); //portA0-A6
						delay_ms(2);


						*GPIOB_ODR = 0x00000004 ; // set PORTB0
						*GPIOB_ODR &= ~(1<<0); //clear portB0
						*GPIOB_ODR &= ~(1<<1); //clear portB1
						//*GPIOB_ODR &= ~(1<<5);
						*GPIOA_ODR = (led[k]); //portA0-A6
						delay_ms(2);


						*GPIOB_ODR = (1<<5); // set PORTB0
						*GPIOB_ODR &= ~(1<<0); // clear portB0
						*GPIOB_ODR &= ~(1<<2); //clear portB2
						*GPIOA_ODR = (led[l]); //portA0-A6
						delay_ms(2);

					}
				  }
			  }
			}
		}
	}
}
