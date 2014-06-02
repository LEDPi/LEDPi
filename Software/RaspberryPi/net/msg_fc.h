#ifndef _H_MSG_FC_
#define _H_MSG_FC_

// START AUTOGENERATED CODE from Excel Sheet on 15:35:25 13.03.2014
// Source File C:\Users\Aiko\Dropbox\Studiprojekt\Documents\Communication\[Communication.xlsx]FC
typedef enum
{
    MSG_HANDSHAKE         = 0x0001, // Tests the connection
    MSG_VERSION_INFO      = 0x0002, // Returns the version Information
    MSG_GMODULE           = 0x0003, // Retrieves or changes the current active graphic module
    MSG_MONO_MONO         = 0x0004, // Handler for the MONO GModule
    MSG_SNAKE_START       = 0x0005, // Starts a game of snake
    MSG_SNAKE_DIRECTION   = 0x0006, // Controls the snakes direction
    MSG_PHOTO_CHANGE      = 0x0007, // Changes the displayed photo
    MSG_BALLS_CHANGE      = 0x0008, // Changes the meta ball settings
    MSG_PLASMA_CHANGE     = 0x0009  // Changes the plasma settings
} msg_fc_t, *p_msg_fc_t; 
// END OF AUTOGENERATED CODE

#endif // _H_MSG_FC_
