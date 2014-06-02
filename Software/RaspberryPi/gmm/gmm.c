#include "gmm/gmm.h"

////////////////////////////////////////////////////////////////////////////////
// private variables
#define GMM_ACTIVATE(ID, MODULE)						\
	{									\
		if(! MODULE ## _init())						\
		{								\
			net_senderror(sender, MODULE_ID_GMM,			\
					ERR_CODES_GMODULE, 2, data);		\
			gmm_int_active_module = MODULE_ID_NO;			\
			log_error(#MODULE " could not be activated");		\
		}								\
		else								\
		{								\
			gmm_int_active_module = ID;				\
			gmm_deinit = MODULE ## _deinit;				\
			log_debug(#MODULE " module was activated");		\
		}								\
	}

#define GMM_CASE(ID, NAME)							\
	case ID:								\
		GMM_ACTIVATE(ID, NAME)						\
	break;

static module_id_t gmm_int_active_module = MODULE_ID_NO;
static void (*gmm_deinit)() = NULL;

////////////////////////////////////////////////////////////////////////////////
// private function declaration
bool gmm_activate(void *sender, uint8_t data[]);

////////////////////////////////////////////////////////////////////////////////
// public functions implementation
void gmm_change(void *sender, uint16_t fc, uint16_t len, uint8_t data[])
{
	if(len != 0 && len != 2)	
		net_senderror(sender, MODULE_ID_GMM, ERR_CODES_UNEXPECTED_PAYLOAD, len, data); 
	else
	{
		if(len == 0 || (len == 2 && gmm_activate(sender, data)))
		{
			uint8_t txData[] = { ((int)gmm_int_active_module) >> 8, 
					     ((int)gmm_int_active_module) & 0xFF };
			net_send(sender, MSG_GMODULE | 0x8000, 2, txData);	
		}
	}
}

module_id_t gmm_active_module()
{
	return gmm_int_active_module;
}

////////////////////////////////////////////////////////////////////////////////
// private functions implementation
bool gmm_activate(void *sender, uint8_t data[])
{
	uint16_t module = data[0] << 8 | data[1];

	if(gmm_int_active_module == module)
		return true;

	if(gmm_deinit != NULL) 
	{
		gmm_deinit();
		gmm_deinit = NULL;
	}

	switch(module)
	{
		GMM_CASE(MODULE_ID_MONO,   mono    )
                GMM_CASE(MODULE_ID_SNAKE,  snake   )
                GMM_CASE(MODULE_ID_PHOTO,  photo   )
                GMM_CASE(MODULE_ID_PLASMA, plasma  )
                GMM_CASE(MODULE_ID_BALL,   ball    )

		case MODULE_ID_NO:
			log_debug("module deactivated");
			gmm_int_active_module = MODULE_ID_NO;
			break;
	
		default:
			net_senderror(sender, MODULE_ID_GMM, ERR_CODES_GMODULE_NA, 0, NULL);
			return NULL;
	}

	return true;
}
