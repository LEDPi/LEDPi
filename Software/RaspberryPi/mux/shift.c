#include "mux/shift.h"

////////////////////////////////////////////////////////////////////////////////
/// Public functions implementations

p_shift_register_t shift_create(uint32_t size, gpio_pin_t pin)
{ 
	p_shift_register_t reg = (p_shift_register_t) malloc( sizeof(shift_register_t) );
	reg->Size = size;
	reg->DS = pin;
	reg->Data = (uint8_t*) malloc( sizeof(uint8_t) * size );
	
	for(int i=0 ; i<size ; i++)
		reg->Data[i] = 0x00;

	GPIO_INP(pin);
	GPIO_OUT(pin);
	GPIO_CLR = (1 << pin);

	MUX_DEBUG("Shift register line created. Length: %d. DS Pin: %d", size, pin);

	return reg;
}

void shift_delete(p_shift_register_t reg)
{
	MUX_DEBUG("Shift regitser line deleted.");

	free(reg->Data);
	free(reg);
}

void shift_set_pin(p_shift_register_t reg, uint32_t register_no, uint8_t bit)
{
	if(register_no < reg->Size)
	{
		if((reg->Data[register_no] & (1 << bit)) > 0)  
			GPIO_SET = (1 << reg->DS);
		else
			GPIO_CLR = (1 << reg->DS);
	}
} 
