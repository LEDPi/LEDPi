#include "main.h"

////////////////////////////////////////////////////////////////////////////////
/// Interrupt Service Routine - is called after the timer runs out.
//////////////////////////////////////////////////////////////////////////////// 
void pit0_isr(void);

////////////////////////////////////////////////////////////////////////////////
/// Initializes the hardware pit0 timer.
//////////////////////////////////////////////////////////////////////////////// 
void init_timer();

static const uint8_t led = 13;

extern "C" int main(void)
{  
	pinMode(led, OUTPUT); 
	digitalWriteFast( led,  HIGH );
	
	Serial.begin(9600);
	
	mux_init();
	init_timer();
	
	int pos = 0;
	while(1)
	{
		if (Serial.available() > 0) 
		{
			digitalWriteFast( led,  LOW );
						
			uint8_t input = Serial.read();
			
			if(input == 0xFE)
			{
				pos = 0;		
				mux_swap();				
			}  else if(input == 0xFF)
			{
			//	mux_swap();
			}
			else
			{
				if(pos < sizeof(mux_buffer_t))
				{
					((uint8_t *)mux_rec_buffer)[pos++] = input;
				}
			}
            
			digitalWriteFast( led,  HIGH );
		}
    } 
}

void pit0_isr(void)
{
	// digitalWrite( 13,  !digitalRead(13) );
	
	mux_plex();
	
	// Reset interrupt flag to 1 (even if the datashet suggest 0)
	PIT_TFLG0 = 1; 
}

void init_timer()
{
	// There are 4 pit timer [0 .. 3] but the PITimer 3 is already occupied by some
	// internal arduino / teensy functionality and can therefore not be used.

	// 12.2.13 System Clock Gating Control Register 6 (SIM_SCGC6)
	// [PDF Page 256]
	//
	// Enable the interal timers.
	//
	// Bit: 23: 1 clock enables.
	SIM_SCGC6 |= SIM_SCGC6_PIT;
		
	// There are 4 pit timer [0 .. 3] but the PITimer 3 is already occupied by some
	// internal arduino / teensy functionality and can therefore not be used.

	// 37.3.1 PIT Module Control Register (PIT_MCR)
	// [PDF Page 903]
	//
	// Bit: 31 - 2 1 0
	// Val:  0 0 0 0 0 -> 0x00
	//       | | | | +-- FRZ  - Stop Timer in Debug mode 	[0 = do not stop]
	//       | | | +---- MDIS - Enable Clock 				[0 = clock enabled]
	//       +-+-+------ Reserved
	PIT_MCR = 0x00;
	
	// 37.3.2 Timer Load Value Register (PIT_LDVALn)
	// [PDF Page 904]
	//
	// Represents only the start value, to read the current timer valie use
	// PIT_CVALn [PDF Page 905].
	//
	// Bit: 31 - 0
	// Val:  0 0 0 -> 0x00
	//       +-+-+------ Timeout-> if timeout reaches 0 a interrupt will be triggered.
	PIT_LDVAL0 = PIT0_LDVAL;

	// 37.3.4 Timer Control Register (PIT_TCTRLn)
	// [PDF Page 905]
	//
	// Bit: 31 - 3 2 1 0
	// Val:  0 0 0 0 1 1 -> 0x02
    //       | | | | | +-- TEN - timer enable 							[0 = timer is enabled]
	//       | | | | +---- TIE - timer interrupt enable 				[0 = interupts are disabled]
	//       | | | +------ CHN - chains this timer to the previous one 	[0 = not chained]
	//       +-+-+------ Reserved
	PIT_TCTRL0 = 0x03;	
	
	// 37.3.5 Timer Flag Register (PIT_TFLGn)
	// [PDF Page 906]
	//
	// Readonly field, writing to this field will not trigger an interrupt and won't
	// have any effect.
	//
	// Bit: 31 - 1 0
	// Val:  0 0 0 0 -> 0x00
        //       | | | +-- TIF - timer interrupt flag 0 = no timeout occured]
	//       +-+-+------ Reserved
        //
        // It seems that in contradiction to the datasheet this is an isr acknowledge. Each isr has to set it
        // to 1, otherwise the isr will not be called again.
	PIT_TFLG0 = 0x01;	
	
	// enables the interrupt
	NVIC_ENABLE_IRQ(IRQ_PIT_CH0);
}