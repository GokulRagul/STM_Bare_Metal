/*
 * arm.h
 *
 *  Created on: Jan 13, 2025
 *      Author: gokul
 */

#ifndef ARM_H_
#define ARM_H_

struct rcc_config
{
	unsigned int CR;  				// 0X40023800
	unsigned int PPLCFGR;			// 0X40023804
	unsigned int CFGR;				// 0X40023808
	unsigned int CIR;				// 0X4002380C
	unsigned int AHB1RSTR;			// 0X40023810
	unsigned int AHB2RSTR;			// 0X40023814
	unsigned int RSD0;				// 0X40023818
	unsigned int RSD1;				// 0X4002381C
	unsigned int APB1RSTR;			// 0X40023820
	unsigned int APB2RSTR;			// 0X40023824
	unsigned int RSD2;				// 0X40023828
	unsigned int RSD3;				// 0X4002382C
	unsigned int AHB1ENR;			// 0X40023830
	unsigned int AHB2ENR;			// 0X40023834
	unsigned int RSD4;				// 0X40023838
	unsigned int RSD5;				// 0X4002383C
	unsigned int APB1ENR;		    // 0X40023840
	unsigned int APB2ENR;           // 0X40023844
	unsigned int RSD6;				// 0X40023848
	unsigned int RSD7;  			// 0X4002384C
	unsigned int AHB1LPENR;			// 0X40023850
	unsigned int AHB2LPENR;			// 0X40023854
	unsigned int RSD8;				// 0X40023858
	unsigned int RSD9;				// 0x4002385c
	unsigned int APB1LPENR; 		// 0x40023860
	unsigned int APB2LPENR;			// 0x40023864
	unsigned int RSD10;				// 0x40023868
	unsigned int RSD11;				// 0x4002386c
	unsigned int BDCR;				// 0x40023870
	unsigned int CSR;				// 0x40023874
	unsigned int RSD12;				// 0x40023878
	unsigned int RSD13;				// 0x4002387c
	unsigned int SSCGR;
	unsigned int PLLI2SCFGR;
	unsigned int RSD14;
	unsigned int DCKCFGR;
};
volatile struct rcc_config *RCC = (volatile struct rcc_config *)0x40023800;

struct port_config
{
	unsigned int MODER;
	unsigned int OTYPER;
	unsigned int OSPEEDER;
	unsigned int PUPDR;
	unsigned int IDR;
	unsigned int ODR;
	unsigned int BSRR;
	unsigned int LCKR;
	unsigned int AFRL;
	unsigned int AFRH;
};

volatile struct port_config *GPIOA = (volatile struct port_config *)0x40020000;

struct timer
{
	unsigned int CR1;
	unsigned int CR2;
	unsigned int SMCR;
	unsigned int DIER;
	unsigned int SR;
	unsigned int EGR;
	unsigned int CCMR1;
	unsigned int RSD1;
	unsigned int CCER;
	unsigned int CNT;
	unsigned int PSC;
	unsigned int ARR;
	unsigned int RSD2;
	unsigned int CCR1;
	unsigned int RSD3;
};

volatile struct timer *TIM10 = (volatile struct timer *)0x40014400;

void rcc_config(void);
void gpio_moder(void);
void peripheral_bus(void);
void led_blinking(void);
void delay_ms(int ms);
void timer_ms(void);

#endif /* ARM_H_ */
