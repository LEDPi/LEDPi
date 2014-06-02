#include "net/msg_handler.h"

void MsgHandlerHandshake(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	log_debug("Handshake Message received");
	
	//check major software verions	
	if(data[0] == (VERSION>>8))
	{	
		// for whatever reason i got an segmentation fault while running the program
		// under ubuntu, if i do not use a preallocated array.
		// the log_debug messes up with printing the given string if it is not pre-
		// allocated, causing the segmentation error.

 		// char *client_type_info;
		char *client_type_info = (char*) malloc(sizeof(char) * 100);
		switch(data[2])
		{
			case CLIENT_ANDROID_APP: 	//client_type_info = "Android App";
				strcpy(client_type_info, "Android App");
				break;
			case CLIENT_WEBSITE:		//client_type_info = "Website";
				strcpy(client_type_info, "Website");
				break;
			case CLIENT_WINDOWS_APP:	//client_type_info = "Windows Application";
				strcpy(client_type_info, "Windows Application");
				break;
			default : 			//client_type_info = "Unkown";
				strcpy(client_type_info, "Unknown");
		}

		log_debug("Versions match Client:[%s]", client_type_info);

		const int data_len = 5;
		uint8_t data_to_send[] = {VERSION >> 8, VERSION & 0xFF, MUX_WIDTH, MUX_HEIGHT, MUX_COLOR_DEPTH};
		net_send(sender, fc|0x8000, data_len, data_to_send);
		free(client_type_info);
	}
	else
	{
		log_debug("Client and Raspi software verions do not match");
		net_senderror(sender, MODULE_ID_COM, ERR_CODES_VERSION, 0, NULL);
	}
}

void MsgHandlerVersionInfo(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	DEBUG("Version Info Message received");

	const int num_modules = 9;	// number of modules late please count active modules
	const int num_data_module = 4;
	uint8_t data_to_send[num_modules * num_data_module] =
   	{ 
		MODULE_ID_MUX    >> 8, MODULE_ID_MUX    & 0xFF, MUX_VERSION    >> 8, MUX_VERSION    & 0xFF,
	   	MODULE_ID_COM    >> 8, MODULE_ID_COM    & 0xFF, NET_VERSION    >> 8, NET_VERSION    & 0xFF,
	   	MODULE_ID_GUI    >> 8, MODULE_ID_GUI    & 0xFF, GUI_VERSION    >> 8, GUI_VERSION    & 0xFF,
		MODULE_ID_GMM    >> 8, MODULE_ID_GMM    & 0xFF, GMM_VERSION    >> 8, GMM_VERSION    & 0xFF,
		MODULE_ID_MONO   >> 8, MODULE_ID_MONO   & 0xFF, MONO_VERSION   >> 8, MONO_VERSION   & 0xFF,
		MODULE_ID_SNAKE  >> 8, MODULE_ID_SNAKE  & 0xFF, SNAKE_VERSION  >> 8, SNAKE_VERSION  & 0xFF,
		MODULE_ID_PHOTO  >> 8, MODULE_ID_PHOTO  & 0xFF, PHOTO_VERSION  >> 8, PHOTO_VERSION  & 0xFF,
		MODULE_ID_PLASMA >> 8, MODULE_ID_PLASMA & 0xFF, PLASMA_VERSION >> 8, PLASMA_VERSION & 0xFF,
		MODULE_ID_BALL   >> 8, MODULE_ID_BALL   & 0xFF, BALL_VERSION   >> 8, BALL_VERSION   & 0xFF
	};

	net_send(sender,fc|0x8000,num_modules*num_data_module,data_to_send);
}
