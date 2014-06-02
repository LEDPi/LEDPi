#include "gmm/photo.h"

bool photo_init()
{
 	draw_picture( photo_pi );
	mux_swap_buffer();
	
	return true;
}

void MsgPhoto_Change(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	if(len == 2)
	{
		//Client wants to change the picture

		uint16_t recv_photo_id = data[0] << 8| data[1];
		p_draw_color_t desired_photo;		

		switch(recv_photo_id)
		{
			case 0x0001:	
					desired_photo = (p_draw_color_t) photo_pi;
					break;
			case 0x0002:
					desired_photo = (p_draw_color_t) Linux;
					break;
			case 0x0003:
					desired_photo = (p_draw_color_t) Android_1;
					break;
			case 0x0004:
					desired_photo = (p_draw_color_t) Android_2;
					break;
			case 0x0005:
					desired_photo = (p_draw_color_t) Smiley;
					break;

			default: 
					log_error("Unkown Picture ID");
					return;		
		}

		draw_picture((p_draw_buffer_t) desired_photo);
		mux_swap_buffer(); 
		
	}
	else
	{
		log_error("Incorrect data length for MsgPhoto_Change");
	}
}


void photo_deinit()
{
}
