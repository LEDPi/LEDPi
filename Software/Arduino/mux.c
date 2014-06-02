#include "mux.h"

#define SHIFT_LINE(LINE, DS_PIN)		\
	static shift_t LINE = 				\
	{									\
		.Size = MUX_SHIFT_LINE_LEN,		\
		.Data = MUX_SHIFT_DEFAULT_VAL,	\
		.DS	  =	(DS_PIN)				\
	}
	
#define SET_COLOR_BIT(ROW, COL, POS, COLOR, REG)		    	    										\
	{																										\
		if( mux_dsp_buffer[ (ROW) ][ (COL) ].COLOR > mux_color )											\
		{																									\
			(REG)->Data[ shift_reg ] |= shift_bit;															\
		}																									\
	}
	
////////////////////////////////////////////////////////////////////////////////
// variable implementation

SHIFT_LINE( line0, MUX_MODUL_2_DS );
SHIFT_LINE( line1, MUX_MODUL_1_DS );
SHIFT_LINE( line2, MUX_MODUL_0_DS );
SHIFT_LINE( line3, MUX_MODUL_5_DS );
SHIFT_LINE( line4, MUX_MODUL_4_DS );
SHIFT_LINE( line5, MUX_MODUL_3_DS );
SHIFT_LINE( line6, MUX_MODUL_8_DS );
SHIFT_LINE( line7, MUX_MODUL_7_DS );
SHIFT_LINE( line8, MUX_MODUL_6_DS );

static shift_mgr_t mux_shift_mgr = 
{
	.ShiftRegister = 	{	
							&line0, 
							&line1, 
							&line2, 
							&line3, 
							&line4, 
							&line5, 
							&line6, 
							&line7, 
							&line8 
						},
						
	.MaxRegisterLen = MUX_SHIFT_LINE_LEN,
	.Written 		= false				,
	.SHCP 			= MUX_SHCP			,
	.STCP 			= MUX_STCP
};

static volatile p_shift_mgr_t mux_shift_mgr_p = &mux_shift_mgr;

static mux_buffer_t mux_buffer1;
static mux_buffer_t mux_buffer2;

volatile        p_mux_buffer_t mux_rec_buffer; // receive buffer
volatile static p_mux_buffer_t mux_dsp_buffer; // display buffer
	
volatile bool mux_dirty_swap = false;

volatile static uint8_t mux_row	  = 0;
volatile static uint8_t mux_color = 0;

////////////////////////////////////////////////////////////////////////////////
// function declaration

inline void mux_internal_swap_buffer() { p_mux_buffer_t tmp = mux_rec_buffer; mux_rec_buffer = mux_dsp_buffer; mux_dsp_buffer = tmp; mux_dirty_swap = false; }

void mux_clear_register();
void mux_enable_row();


////////////////////////////////////////////////////////////////////////////////
// function implementation

void mux_init() 
{
	pinMode( MUX_SHCP, 		 OUTPUT ); 
	pinMode( MUX_STCP, 		 OUTPUT ); 
	pinMode( MUX_MODUL_0_DS, OUTPUT ); 
	pinMode( MUX_MODUL_1_DS, OUTPUT ); 
	pinMode( MUX_MODUL_2_DS, OUTPUT ); 
	pinMode( MUX_MODUL_3_DS, OUTPUT ); 
	pinMode( MUX_MODUL_4_DS, OUTPUT ); 
	pinMode( MUX_MODUL_5_DS, OUTPUT ); 	
	pinMode( MUX_MODUL_6_DS, OUTPUT ); 
	pinMode( MUX_MODUL_7_DS, OUTPUT ); 
	pinMode( MUX_MODUL_8_DS, OUTPUT ); 
	
	digitalWrite( MUX_SHCP, HIGH );
	digitalWrite( MUX_STCP, HIGH );
	
	digitalWrite( MUX_MODUL_0_DS, LOW ); 
	digitalWrite( MUX_MODUL_1_DS, LOW ); 
	digitalWrite( MUX_MODUL_2_DS, LOW ); 
	digitalWrite( MUX_MODUL_3_DS, LOW ); 
	digitalWrite( MUX_MODUL_4_DS, LOW ); 
	digitalWrite( MUX_MODUL_5_DS, LOW ); 	
	digitalWrite( MUX_MODUL_6_DS, LOW ); 
	digitalWrite( MUX_MODUL_7_DS, LOW ); 
	digitalWrite( MUX_MODUL_8_DS, LOW ); 
	
	memcpy(mux_buffer1, default_background, sizeof(mux_buffer_t));
	memcpy(mux_buffer2, default_background, sizeof(mux_buffer_t));
		
	mux_rec_buffer = mux_buffer1;	
	mux_dsp_buffer = mux_buffer2;
	
	mux_row = mux_color = 0;
}

void mux_swap()
{
	mux_dirty_swap = true;
	while(mux_dirty_swap);
}

void mux_plex()
{
	if( ++mux_row >= 10 )
	{
		mux_row = 0;
		
		if( ++mux_color >= MUX_COLOR_DEPTH )
		{
			mux_color = 0;
			
			if( mux_dirty_swap )
				mux_internal_swap_buffer();
		}		
	}
		
	mux_clear_register();
	mux_enable_row();
	
	for( int col=0 ; col < 10; col++ )
	{		
		uint8_t pos = col * 3;    		
		
		uint8_t shift_reg = (((pos) + MUX_COL_OFFSET) >> 3);
		uint8_t shift_bit = (1 << (((pos) + MUX_COL_OFFSET) % 8));
		
		SET_COLOR_BIT( mux_row +  0, col +  0, pos, g, mux_shift_mgr.ShiftRegister[0] );		
		SET_COLOR_BIT( mux_row +  0, col + 10, pos, g, mux_shift_mgr.ShiftRegister[1] );		
		SET_COLOR_BIT( mux_row +  0, col + 20, pos, g, mux_shift_mgr.ShiftRegister[2] );		
		SET_COLOR_BIT( mux_row + 10, col +  0, pos, g, mux_shift_mgr.ShiftRegister[3] );
		SET_COLOR_BIT( mux_row + 10, col + 10, pos, g, mux_shift_mgr.ShiftRegister[4] );		
		SET_COLOR_BIT( mux_row + 10, col + 20, pos, g, mux_shift_mgr.ShiftRegister[5] );		
		SET_COLOR_BIT( mux_row + 20, col +  0, pos, g, mux_shift_mgr.ShiftRegister[6] );		
		SET_COLOR_BIT( mux_row + 20, col + 10, pos, g, mux_shift_mgr.ShiftRegister[7] );		
		SET_COLOR_BIT( mux_row + 20, col + 20, pos, g, mux_shift_mgr.ShiftRegister[8] );	
		
		++pos;	
		shift_reg = (((pos) + MUX_COL_OFFSET) >> 3);
		shift_bit = (1 << (((pos) + MUX_COL_OFFSET) % 8));
		
		SET_COLOR_BIT( mux_row +  0, col +  0, pos, b, mux_shift_mgr.ShiftRegister[0] );		
		SET_COLOR_BIT( mux_row +  0, col + 10, pos, b, mux_shift_mgr.ShiftRegister[1] );		
		SET_COLOR_BIT( mux_row +  0, col + 20, pos, b, mux_shift_mgr.ShiftRegister[2] );		
		SET_COLOR_BIT( mux_row + 10, col +  0, pos, b, mux_shift_mgr.ShiftRegister[3] );
		SET_COLOR_BIT( mux_row + 10, col + 10, pos, b, mux_shift_mgr.ShiftRegister[4] );		
		SET_COLOR_BIT( mux_row + 10, col + 20, pos, b, mux_shift_mgr.ShiftRegister[5] );		
		SET_COLOR_BIT( mux_row + 20, col +  0, pos, b, mux_shift_mgr.ShiftRegister[6] );		
		SET_COLOR_BIT( mux_row + 20, col + 10, pos, b, mux_shift_mgr.ShiftRegister[7] );		
		SET_COLOR_BIT( mux_row + 20, col + 20, pos, b, mux_shift_mgr.ShiftRegister[8] );	
		
		++pos;
		shift_reg = (((pos) + MUX_COL_OFFSET) >> 3);
		shift_bit = (1 << (((pos) + MUX_COL_OFFSET) % 8));
   		
		SET_COLOR_BIT( mux_row +  0, col +  0, pos, r, mux_shift_mgr.ShiftRegister[0] );		
		SET_COLOR_BIT( mux_row +  0, col + 10, pos, r, mux_shift_mgr.ShiftRegister[1] );		
		SET_COLOR_BIT( mux_row +  0, col + 20, pos, r, mux_shift_mgr.ShiftRegister[2] );			
		SET_COLOR_BIT( mux_row + 10, col +  0, pos, r, mux_shift_mgr.ShiftRegister[3] );
		SET_COLOR_BIT( mux_row + 10, col + 10, pos, r, mux_shift_mgr.ShiftRegister[4] );		
		SET_COLOR_BIT( mux_row + 10, col + 20, pos, r, mux_shift_mgr.ShiftRegister[5] );		
		SET_COLOR_BIT( mux_row + 20, col +  0, pos, r, mux_shift_mgr.ShiftRegister[6] );		
		SET_COLOR_BIT( mux_row + 20, col + 10, pos, r, mux_shift_mgr.ShiftRegister[7] );		
		SET_COLOR_BIT( mux_row + 20, col + 20, pos, r, mux_shift_mgr.ShiftRegister[8] );			
	}
		
	shift_mgr_write(mux_shift_mgr_p);
	shift_mgr_activate( mux_shift_mgr_p );
}

void mux_clear_register()
{
	memset( mux_shift_mgr.ShiftRegister[0]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[1]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[2]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[3]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[4]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[5]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[6]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[7]->Data, 0x00, MUX_SHIFT_LINE_LEN );
	memset( mux_shift_mgr.ShiftRegister[8]->Data, 0x00, MUX_SHIFT_LINE_LEN );
}

void mux_enable_row()
{
	int offset = ((mux_row + MUX_ROW_OFFSET) >> 3);
	int value  = (1 << (mux_row + MUX_ROW_OFFSET) % 8);
	
	mux_shift_mgr.ShiftRegister[0]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[1]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[2]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[3]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[4]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[5]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[6]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[7]->Data[ offset ] |= value;
	mux_shift_mgr.ShiftRegister[8]->Data[ offset ] |= value;
}