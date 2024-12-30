// IR in PuLL down Resistor

//rcc_config
volatile unsigned int  *RCC_CR = (volatile unsigned int *)0x40023800;
volatile unsigned int  *RCC_CFGR = (volatile  unsigned int *)0x40023808;
volatile unsigned int  *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;

//port config

volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR = (volatile unsigned int *)0x40020014;
volatile unsigned int *GPIOA_PUPDR = (volatile unsigned int *)0x4002000c;
volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;
volatile unsigned int *GPIOB_IDR = (volatile unsigned int *)0x40020410;
volatile unsigned int *GPIOB_PUPDR = (volatile unsigned int *)0x4002040c;




void rcc_config(void);
void peripheral_bus(void);
void gpio_moder(void);
void gpio_pupdr(void);
void delay_ms(int ms);
void led_blinking(void);

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
	//CONTROL REGISTER

	//RCC_CR PAGE NO :103

	*RCC_CR  = *RCC_CR & (~(1 << 16)); //HESON CLOCK DISABLE
	*RCC_CR  = *RCC_CR | (1 << 16); //HESON CLOCK ENABLE

	while (!(*RCC_CR & (1 << 17)));

	// 	CLOCK CONFIG

	*RCC_CFGR = *RCC_CFGR  & (~(3 << 1));//clear system clock switch
	*RCC_CFGR = *RCC_CFGR  | (1 << 0); //HSC selected as system clock

	while (!(*RCC_CFGR & (1 << 2))); //HSC oscillator used as system clock
}

void peripheral_bus()
{
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 0);//IO PORTA clock enable 
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1 << 1);//IO PORTB clock enable 
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
        //GPIOC Register starting page number :157
	*GPIOA_MODER = *GPIOA_MODER | (1 << 0);// general purpose output and input  open_drain

    *GPIOB_MODER = *GPIOB_MODER & (~0x00000003);// general purpose output and input  open_drain

    gpio_pupdr();
}

void gpio_pupdr()
{

	*GPIOB_PUPDR = *GPIOB_PUPDR | (1 << 1); // pull down regsistor
}

void led_blinking()
{
	if (*GPIOB_IDR  & (0x00000001))
	{
		*GPIOA_ODR = *GPIOA_ODR | (1 << 0);

	}
	else
	{
		*GPIOA_ODR = *GPIOA_ODR  | (1 << 0);
		delay_ms(10);
		*GPIOA_ODR = *GPIOA_ODR & (~1 << 0);
		delay_ms(10);
	}
}
