#ifndef _H_SHIFT_REGISTER_
#define _H_SHIFT_REGISTER_

typedef struct
{
	uint32_t Size;
	uint8_t *Data; 
	gpio_pin_t DS;
} shift_register_t, *p_shift_register_t;

#endif // _H_SHIFT_REGISTER_
