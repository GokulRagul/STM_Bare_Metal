#ifndef ARM_H_
#define ARM_H_

struct rcc_config
{
	unsigned int CR;
	unsigned int PLLCFGR;
	unsigned int CFGR;
	unsigned int CIR;
	unsigned int AHB1RSTR;
	unsigned int AHB2RSTR;
	unsigned int RSD0;
	unsigned int RSD1;
	unsigned int APB1RSTR;
	unsigned int APB2RSTR;
	unsigned int RSD2;
	unsigned int RSD3;
	unsigned int AHB1ENR;
	unsigned int AHB2ENR;
	unsigned int RSD4;
	unsigned int RSD5;
	unsigned int APB1ENR;
	unsigned int APB2ENR;
	unsigned int RSD6;
	unsigned int RSD7;
	unsigned int AHB1LPENR;
	unsigned int AHB2LPENR;
	unsigned int RSD8;
	unsigned int RSD9;
	unsigned int APB1LPENR;
	unsigned int APB2LPENR;
	unsigned int RSD10;
	unsigned int RSD11;
	unsigned int BDCR;
	unsigned int CSR;
	unsigned int RSD12;
	unsigned int RSD13;
	unsigned int SSCGR;
	unsigned int PLLI2SCFGR;
	unsigned int RSD14;
	unsigned int DCKCFGR;

};
volatile struct rcc_config *RCC = (volatile struct rcc_config *)0x40023800; // clock control register

struct port_config
{
	unsigned int MODER;
	unsigned int OTYPER;
	unsigned int OSPEEDR;
	unsigned int PUPDR;
	unsigned int IDR;
	unsigned int ODR;
};


volatile struct port_config *GPIOC = (volatile struct port_config *)0x40020800; // general portA  mode register


void rcc_config(void);
void gpioa_moder(void);
void peripheral_bus(void);
void led_blinking(void);
void delay_ms(int ms);

#endif /* ARM_H_ */




