#include "mux/gpio.h"

#ifndef DESKTOP

volatile unsigned *gpio;

void gpio_init()
{
	int mem_fd;
	if( (mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) 
	{
		log_error("Can't open /dev/mem");
		exit(-1);
	}

	void *gpio_map = mmap( 
		NULL,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		mem_fd,
		GPIO_BASE
	);

	close(mem_fd);

	if(gpio_map == MAP_FAILED)
	{
		log_error("mmap error %d", gpio_map);
		exit(-1);
	}

	gpio = (volatile unsigned*) gpio_map;
	
	gpio_clear_all();

	MUX_DEBUG("GPIO Pins Initialized and Resetted"); 
}

void gpio_clear_all()
{
	GPIO_CLR = (1 << GPIO_02) | (1 << GPIO_03) | (1 << GPIO_04) |
		   (1 << GPIO_07) | (1 << GPIO_08) | (1 << GPIO_09) |
		   (1 << GPIO_10) | (1 << GPIO_11) | (1 << GPIO_11) |
		   (1 << GPIO_14) | (1 << GPIO_15) | (1 << GPIO_15) |
		   (1 << GPIO_17) | (1 << GPIO_18) | (1 << GPIO_22) |
		   (1 << GPIO_23) | (1 << GPIO_24) | (1 << GPIO_25) |
		   (1 << GPIO_27);
}

#else

unsigned gpio_dummy;

void gpio_init()
{
	gpio_dummy = 0;
}

void gpio_clear_all()
{
}

#endif
