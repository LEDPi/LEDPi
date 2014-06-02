#ifndef _H_GPIO_
#define _H_GPIO_

////////////////////////////////////////////////////////////////////////////////
// FILE: gpio
// DESC: enables the gpio p1 pin access using the fast direct memory access.
// 	 Benchmarks found on 
//	 "codelife.com/2012/07/03/benchmarking-raspberry-pi-gpio-speed"
//	 show that it is possible achieve up to 25MHz square wave frequency 
//	 using this method.
////////////////////////////////////////////////////////////////////////////////
  
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "gui/logger.h"
#include "mux/mux_debug.h"
#include "mux/gpio_pin.h"

#ifndef DESKTOP
#	define BLOCK_SIZE (4 * 1024)

#	define BCM2708_PERI_BASE	0x20000000
#	define GPIO_BASE		(BCM2708_PERI_BASE + 0x200000)
#endif

/// ////////////////////////////////////////////////////////////////////////////
// Initializes the gpio access module
/// //////////////////////////////////////////////////////////////////////////// 
void gpio_init(); 
  
/// //////////////////////////////////////////////////////////////////////////// 
// Sets the given pin to an input pin. Always call this function, before calling
// GPIO_OUT or GPIO_ALT.
/// //////////////////////////////////////////////////////////////////////////// 
#ifdef DESKTOP
#	define GPIO_INP(pin)
#else
#	define GPIO_INP(pin) 		*(gpio + ( (pin) / 10) ) &= ~(7 << (( (pin) % 10) * 3))
#endif

/// //////////////////////////////////////////////////////////////////////////// 
// Sets the given pin to an output pin. Call GPIO_INP before this function.
/// ////////////////////////////////////////////////////////////////////////////  
#ifdef DESKTOP
#	define GPIO_OUT(pin)
#else
#	define GPIO_OUT(pin)		*(gpio + ( (pin) / 10) ) |=  (1 << (( (pin) % 10) * 3))
#endif

/// //////////////////////////////////////////////////////////////////////////// 
// Enables the gpio pin's alternative function, if the pin has one. Always call
// GPIO_INP before calling this function.
/// //////////////////////////////////////////////////////////////////////////// 
#ifdef DESKTOP
#	define GPIO_ALT(pin, a)
#else
#	define GPIO_ALT(pin, a) *(gpio + (( (pin) / 10) ) ) |= (( (a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << (( (pin) % 10) * 3))
#endif

/// //////////////////////////////////////////////////////////////////////////// 
// Sets the pins which bits are 1, ignores all other values. Example usage:
//	GPIO_SET = (1 << GPIO_02) | (1 << GPIO_03);
/// //////////////////////////////////////////////////////////////////////////// 
#ifdef DESKTOP
#	define GPIO_SET gpio_dummy
#else
#	define GPIO_SET *(gpio +  7)
#endif

/// //////////////////////////////////////////////////////////////////////////// 
// Clears the pins which bits are 1, ignores all other values. Example usage:
//	GPIO_CLR = (1 << GPIO_02) | (1 << GPIO_03); 
/// //////////////////////////////////////////////////////////////////////////// 
#ifdef DESKTOP
#	define GPIO_CLR	gpio_dummy
#else
#	define GPIO_CLR *(gpio + 10) 
#endif

/// ////////////////////////////////////////////////////////////////////////////
// Resets all output pins. Sets the pins to Low.
/// ////////////////////////////////////////////////////////////////////////////
void gpio_clear_all();

// This global variable is needed, because the gpio functions are only macros 
// for accessing the memory behind this pointer correctly.
#ifdef DESKTOP
extern unsigned gpio_dummy;
#else
extern volatile unsigned * gpio;   
#endif

#endif // _H_GPIO_
