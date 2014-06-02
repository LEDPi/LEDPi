#include "shiftmgr.h"

extern  "C" inline void shift_mgr_toggle(uint8_t pin)
{
	digitalWriteFast( pin, LOW  );
	
	asm("nop");asm("nop");asm("nop");
	
	digitalWriteFast( pin, HIGH );
}

extern "C" void shift_mgr_write(p_shift_mgr_t mgr)
{
	mgr->Written = true;

	for(int reg=mgr->MaxRegisterLen - 1 ; reg >=0 ; --reg)
	{
		for(int bit=0 ; bit<8 ; bit++)
		{
			for(uint8_t shiftline = 0 ; shiftline < MUX_PANEL_COUNT ; ++shiftline)
			{	
				shift_set_pin(mgr->ShiftRegister[shiftline], reg, bit);	
			}

			shift_mgr_toggle( mgr->SHCP );
		}
	}
}

extern "C" void shift_mgr_activate(p_shift_mgr_t mgr)
{
	if(mgr->Written)
	{
		shift_mgr_toggle( mgr->STCP );
		mgr->Written = false;
	}
}