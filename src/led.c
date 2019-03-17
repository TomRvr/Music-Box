#include "sys/devices.h"
#include "sys/cm4.h"
#include "sys/clock.h"

void led_init() {
  /* Configure PA4-PA10 as outputs, push-pull, high speed*/
	GPIOA.MODER = (GPIOA.MODER & ~(0x3FFF<<8)) | (0x1555<<8);
	GPIOA.OTYPER  &= ~(0x7F<<4);
	GPIOA.OSPEEDR |= (0x3FFF<<10);

}


void led_tri_set(uint32_t status) {
  GPIOA.ODR = (GPIOA.ODR & ~(7<<8) ) | (1<<(8+status));

}


