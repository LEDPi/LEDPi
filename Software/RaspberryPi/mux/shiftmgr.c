#include "mux/shiftmgr.h"

////////////////////////////////////////////////////////////////////////////////
/// Private functions declarations 

void shift_mgr_free_shift_line_memory(void *reg);

////////////////////////////////////////////////////////////////////////////////
/// Public functions implementations

p_shift_mgr_t shift_mgr_create(gpio_pin_t shcp, gpio_pin_t stcp)
{
	p_shift_mgr_t mgr = (p_shift_mgr_t) malloc( sizeof(shift_mgr_t) );
	mgr->ShiftRegister = ll_create(&shift_mgr_free_shift_line_memory);
	mgr->MaxRegisterLen = 0;
	mgr->Written = false;
	mgr->SHCP = shcp;
	mgr->STCP = stcp;
	
	GPIO_INP(shcp);
	GPIO_OUT(shcp);
	GPIO_SET = (1 << shcp);

	GPIO_INP(stcp);
	GPIO_OUT(stcp);
	GPIO_SET = (1 << stcp);

	MUX_DEBUG("Shift register manager created");

	return mgr;
}

void shift_mgr_delete(p_shift_mgr_t mgr)
{
	MUX_DEBUG("Shift register manager deleted");

	ll_delete(mgr->ShiftRegister);
	free(mgr);
}

void shift_mgr_register(p_shift_mgr_t mgr, p_shift_register_t reg)
{
	MUX_DEBUG("Shift register line registered");

	ll_append(mgr->ShiftRegister, reg);

	if(reg->Size > mgr->MaxRegisterLen)
		mgr->MaxRegisterLen = reg->Size;
}

void shift_mgr_write(p_shift_mgr_t mgr)
{
	mgr->Written = true;

	for(int reg=mgr->MaxRegisterLen ; reg >=0 ; --reg)
	{
		for(int bit=0 ; bit<8 ; bit++)
		{
			ll_first(mgr->ShiftRegister);
			while(ll_next(mgr->ShiftRegister))
			{	
				shift_set_pin((p_shift_register_t) ll_get(mgr->ShiftRegister), reg, bit);	
			}
		
			GPIO_CLR = 1 << mgr->SHCP;
			GPIO_SET = 1 << mgr->SHCP;
		}
	}
}

void shift_mgr_activate(p_shift_mgr_t mgr)
{
	if(mgr->Written)
	{
		GPIO_CLR = 1 << mgr->STCP;
		GPIO_SET = 1 << mgr->STCP;
		mgr->Written = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Private functions implementations

void shift_mgr_free_shift_line_memory(void *reg)
{
	free( (p_shift_register_t) reg);
}
