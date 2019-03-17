#include <stdint.h>
#include "sys/cm4.h"
#include "sys/devices.h"
#include "sys/init.h"
#include "sys/clock.h"
#include "sys/serial_io.h"
#include "button.h"
#include "systick.h"
#include "led.h"
#include "fonctions.h"

#define T_pause 10	/*Temps de pause entre les notes en ms*/ 
#define T_veille 3	/*Nombre de mélodies avant la mise en veille*/
#define Temps 500	/*Base de temps des notes, en ms*/

/*Pointeurs mélodies*/
extern uint16_t *ptN_melodie;	/*pointeur sur les notes de la melodie*/
extern uint16_t *ptD_melodie;	/*pointeur sur les durees de la melodie*/

extern int8_t modeS;
int32_t volatile veille = 0;
int16_t volatile CPT = 0;
uint8_t volatile flag=0;
uint8_t volatile pause=0;
uint8_t volatile i=0;	/*Compteur global pour parcourir les tableaux des mélodies*/
uint8_t couleur = 0;	/*Couleur de la LED RGB (0,1,2)*/

/* Handler d'interruption systick - duree des notes */
void __attribute__((interrupt)) SysTick_Handler() {
	if(pause !=1)
	{
		CPT++;
	}	
	else
	{
		CPT++;
		if(CPT>=T_pause){	/*pause finie*/
			CPT = 0;
			pause =0;
			TIM2.CR1^=1;	/*redemarrage timer*/
			led_tri_set(couleur);
			if(couleur>=2)
			{
				couleur=0;
			}
			else
			{
				couleur++;
			}
		}
	}
}

/* Handler d'interruption du bouton sur PB8 - ON/OFF */
void __attribute__((interrupt)) EXTI9_5_Handler() 
{	
	EXTI.PR |= (1<<8);
	TIM2.CR1^=1;	/*inversion du bit d'activation de l'horloge du timer (ON/OFF)*/
	SysTick.CTRL^=1;/*inversion du bit d'activation de l'horloge du systick (ON/OFF)*/
	led_tri_set(0);	/*LED Rouge*/
	veille = 0;
}

int main() {
	
	/*Initialisation des ports utiles */
	enable_GPIOA();
	enable_GPIOB(); 
	enable_GPIOC();
	
	/*Activation du potentiometre pour regler le volume*/
	configuration_potentiometre();
	enable_SYSCFG();
	
	/*Bouton ON/OFF - bouton carte fille*/
	button_init();
	button_irq_init();	/* Enable interrupts (user button PB8)*/
	
	/*Lecture des switchs au demarrage pour selectionner la melodie*/
	select_melodie();	
	
	/*Initialisation des registres du timer 2*/
	init_timer();
	
	/*Initialisation du carré de LEDs et LED RGB*/
	led_init();
	
	/* Initialisation des switchs */
	init_switchs();
	
	/* Enable Systick 1000 Hz, IT toutes les 1ms */
	SysTick_init(1000);

	while (1)
	{
		if(pause !=1)
		{
			TIM2.ARR=ARR_Freq(*(ptN_melodie+i));/*Ajustement de la fréquence de la note a jouer*/
			if(veille>=T_veille){
				veille = 0;
				if(modeS == 1){
					TIM2.CR1 ^=1;		/*Arret timer*/
					SysTick.CTRL^=1;	/*Arrêt systick*/
					led_tri_set(0);		/*LED Rouge*/
				}
			}
			if(CPT>=(Temps *(*(ptD_melodie + i))))	/*prise en compte de la duree de la note*/
			{	
				flag=1;
				CPT = 0;
				TIM2.CR1^=1;	/*arret timer*/
				pause =1;		/*Note finie, pause avant note suivante*/
			}
		}
		if(flag==1)
		{
			if(*(ptN_melodie + i) == 0)	/*Si fin de la melodie*/
			{	
				i=0;	/*Retour au debut*/
				veille++;
			}
			else
			{
				i++;	/*Note suivante*/
			}
			flag = 0;
		}
		select_melodie();	/*Scrutation des switchs pour selectionner la melodie*/
		volume();	/*Reglage du volume et affichage sur les LEDs*/
	}
return 0;
}

