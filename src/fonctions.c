#include <stdint.h>
#include "sys/cm4.h"
#include "sys/devices.h"
#include "sys/init.h"
#include "sys/clock.h"
#include "sys/serial_io.h"
#include "adc.h"
#include "led.h"
#include "notes.c"

extern uint16_t berceuse[2][55];
extern uint16_t colas[2][39];
extern uint16_t clair[2][46];
extern uint16_t salv[2][31];
extern uint16_t noel[2][77];
extern uint16_t marionette[2][27];
extern uint16_t dodo[2][27];
extern uint16_t jacques[2][34];

/*Pointeur selection de musique*/
uint16_t *ptN_melodie;	/*pointeur sur les notes de la melodie*/
uint16_t *ptD_melodie;	/*pointeur sur les durees de la melodie*/

/*Frequence du timer voulue, 100 kHz*/
uint32_t divclk = 100000;

uint8_t modeS;

/*Calcul de la valeur de ARR en fonctions de la frequence de la note*/
uint32_t ARR_Freq(uint16_t f)
{
	return divclk/f;
}

/*Initialisation des registres du timer 2*/
void init_timer()
{	
	GPIOB.MODER &= ~(3<<18);
	GPIOB.MODER |= (1<<19);	/*BUZZER EN SORTIE AF*/
	GPIOB.AFRH &= ~ 0xF0;	/*AF1 dans AFRH9*/
	GPIOB.AFRH |= 1<<4;
	
	enable_TIM2();
	/* Init Timer 2 registre CR1*/
	TIM2.CR1|=0x81;
	
	/* Init Timer 2 registre PSC (prescaler) pour avoir 100kHz */
	TIM2.PSC=get_APB1TIMCLK() / divclk;
	
	/*Periode PWM, ARR_freq(freq_note)*/
	TIM2.ARR=ARR_Freq(1);
	
	/*Rapport cyclique*/
	/*TIM2.CCR2=4;*/
	
	/*PWM mode 1*/	
	TIM2.CCMR1 &= ~(1<<12);	
	TIM2.CCMR1 |= (13<<11);
	
	/*CC2E output*/
	TIM2.CCER |= 0x10;
	
	/*Demarrage du timer*/
	TIM2.EGR |= 1;
}

/*Reglage du potentiometre en entree et du convertisseur*/
void configuration_potentiometre()
{
	GPIOB.MODER &=0x0;
	GPIOB.MODER |=0x3;
	enable_ADC1();
	ADC_set_prediv(1);
	ADC_set_sampling_time(&ADC1,8,7);
	ADC_init_single_channel(&ADC1,8);
}

/*Conversion de la valeur du potentiometre*/
uint32_t mesure_potentiometre()
{
	return ADC_convert_single_channel(&ADC1);
}

/*Initialisation de la barre de 4 switchs - PB3,4,5,6*/
void init_switchs(){
	GPIOB.MODER &= ~ 0x03fc0;	/*input*/
	GPIOB.PUPDR &= ~ 0x03fc0;	/*No pull up/down*/
}

/*Selection de la melodie à jouer*/
/*16 cas possible, de 0 à 15*/
void select_melodie(){
	uint8_t val;
	val = (GPIOB.IDR & 0x038) >> 3;	/*lecture de l'etat des 3 switchs de selection*/
	modeS = (GPIOB.IDR & 0x040) >> 6;	/*lecture du switch 0 :mode infini / 1 : sommeil*/
	switch(val){
		case 0 :
			ptN_melodie = &clair[0][0];
			ptD_melodie = &clair[1][0];
			break;
		case 1 :
			ptN_melodie = &berceuse[0][0];
			ptD_melodie = &berceuse[1][0];
			break;
		case 2:
			ptN_melodie = &colas[0][0];
			ptD_melodie = &colas[1][0];
			break;
		case 3:
			ptN_melodie = &noel[0][0];
			ptD_melodie = &noel[1][0];
			break;
		case 4:
			ptN_melodie = &salv[0][0];
			ptD_melodie = &salv[1][0];
			break;
		case 5:
			ptN_melodie = &marionette[0][0];
			ptD_melodie = &marionette[1][0];
			break;
		case 6:
			ptN_melodie = &dodo[0][0];
			ptD_melodie = &dodo[1][0];
			break;
		case 7:
			ptN_melodie = &jacques[0][0];
			ptD_melodie = &jacques[1][0];
			break;
			
		default :
			ptN_melodie = &clair[0][0];
			ptD_melodie = &clair[1][0];
			break;
	}
}

/*Reglage du volume et affichage sur le carré de LED*/
void volume(){
	uint32_t res;
	res=mesure_potentiometre();		/*mesure de la position du potentiometre [0,4096]*/
	res=(res/210)%20;	/*div res par 210 pour avoir au max 4096/210 = 19 / Rapport cyclique de 0 à 20%*/
	TIM2.CCR2=res;
	
	/* carré de LED */
	switch(res)
		{
		case 0:											/*4 LEDs OFF*/
			GPIOA.ODR&=0xFF0F;
			break;
		case 1: case 2: case 3: case 4: case 5:			/*[1,5] 1 LED ON*/
			GPIOA.ODR&=0xFF0F;
			GPIOA.ODR|=0x0010;
			break;
		case 6: case 7: case 8: case 9: case 10:		/*[6,10] 2 LEDs ON*/
			GPIOA.ODR&=0xFF0F;
			GPIOA.ODR|=0x0030;
			break;
 		case 11: case 12: case 13: case 14: case 15:	/*[11,15] 3 LEDs ON*/
			GPIOA.ODR&=0xFF0F;
			GPIOA.ODR|=0x0070;
			break;
 		case 16: case 17: case 18: case 19: case 20:	/*[15,20] 4 LEDs ON*/
			GPIOA.ODR&=0xFF0F;
			GPIOA.ODR|=0x00F0;
			break;
 		default:
			GPIOA.ODR&=0xFF0F;
			break;
		}
}







