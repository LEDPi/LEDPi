#ifndef _H_GPIO_PIN_
#define _H_GPIO_PIN_

/// //////////////////////////////////////////////////////////////////////////// 
// All available pins on the p1 header.
/// //////////////////////////////////////////////////////////////////////////// 
typedef enum 
{
	GPIO_02	=  2, // PIN  3
	GPIO_03 =  3, // PIN  5
	GPIO_04 =  4, // PIN  7
	GPIO_07 =  7, // PIN 26
	GPIO_08 =  8, // PIN 24
	GPIO_09 =  9, // PIN 21
	GPIO_10 = 10, // PIN 19
	GPIO_11 = 11, // PIN 23
	GPIO_14 = 14, // PIN  8
	GPIO_15 = 15, // PIN 10
	GPIO_17 = 17, // PIN 11
	GPIO_18 = 18, // PIN 12
	GPIO_22 = 22, // PIN 15
	GPIO_23 = 23, // PIN 16
	GPIO_24 = 24, // PIN 18
	GPIO_25 = 25, // PIN 22
	GPIO_27 = 27, // PIN 13

} gpio_pin_t, *pgpio_pin_t;

#endif // _H_GPIO_PIN_
