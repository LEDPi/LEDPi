#include "net/net.h"

////////////////////////////////////////////////////////////////////////////////
// module private variables

static bool net_initialized = false;

static pthread_t net_thread;

static int rxSocket;
static struct sockaddr_in rxAddress;
static pnetbuffer_t buffer;

////////////////////////////////////////////////////////////////////////////////
// private function declaration

////////////////////////////////////////////////////////////////////////////////
// Returns true if the checksum of the message in the message buffer is correct.
// The message buffer contains the fc and the len information, but at the point,
// where this function is needed, those information where already constracted.
// So i'll pass them.
//
// PARAMS:
//	len	the messages lenght
////////////////////////////////////////////////////////////////////////////////
bool net_check_cs(uint16_t len);

////////////////////////////////////////////////////////////////////////////////
// Receives the incoming messages, decodes them and forwards them to the correct
// reveiver.
// This method has the correct syntax to be used as thread entry point.
//
// PARA:
//	void * unnamed: needed to match the thread entry point mehtod signature,
//			but is not used. Passed data will be ignored.
//	return value :	is also not used, function will not return anything.
////////////////////////////////////////////////////////////////////////////////
void *net_run_thread(void *);

////////////////////////////////////////////////////////////////////////////////
// Converts the low nibble of the given number into an hexadecimal character.
// PARA:
//	byte: the byte
////////////////////////////////////////////////////////////////////////////////
char net_hex_to_char(uint8_t byte);

////////////////////////////////////////////////////////////////////////////////
// public function implementation

bool net_init()
{
	buffer = net_buffer_create(NET_BUFSIZE);

	if( (rxSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		log_error("Unable to create socket");
		return false;
	}

	memset(&rxAddress, 0, sizeof(struct sockaddr_in));
	rxAddress.sin_family 		= AF_INET;
	rxAddress.sin_addr.s_addr 	= htonl(INADDR_ANY);
	rxAddress.sin_port 		= htons(NET_PORT);

	if(bind(rxSocket, (struct sockaddr*) &rxAddress, sizeof(struct sockaddr_in)) < 0)
	{
		log_error("Unable to bind socket");
		return false;
	}

	if(!jobstack_init())
	{
		log_error("Unable to initialize jobstack");
		return false;
	}
	net_initialized = true;
	return true;
}

void net_run()
{
	if(!net_initialized) return;

	DEBUG("Start receiving thread");
	if(pthread_create(&net_thread, NULL, net_run_thread, NULL) != 0)
	{
		log_error("Unable to create the receiver thread");
	}

	jobstack_run();
}

void net_close()
{
	if(!net_initialized) return;

	pthread_cancel(net_thread);

	close(rxSocket);
	net_buffer_delete(buffer);

	log_debug("shutdown net module");
}

void net_send(void* senderinfo, uint16_t fc, uint16_t len, uint8_t data[])
{
	int sock;
	struct sockaddr_in client;

	memset(&client, 0, sizeof(sockaddr_in));
	client.sin_family = AF_INET;
	client.sin_port = htons(DEST_PORT);

	if(!inet_aton(((pnetsenderinfo_t)senderinfo)->net_address, &client.sin_addr))
	{
		log_error("The net adress is not valid ");
		return;
	}

	if((sock=socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		log_error("Unable to create sending socket");
		return;
	}

	//Build message and calculate checksum
	uint8_t* tmpmsg = (uint8_t*) malloc(sizeof(uint8_t)*(len+5));
	tmpmsg[0] = (uint8_t) (fc>>8);
	tmpmsg[1] = (uint8_t) fc;
	tmpmsg[2] = (uint8_t) (len>>8);
	tmpmsg[3] = (uint8_t) len;

	uint8_t cs = 0;
	for(int i=0; i<4;i++)
	{
		cs = (cs + tmpmsg[i]) % 0xFF;
	}

	for(int i=0; i<len; i++)
	{
		tmpmsg[i+4] = data[i];
		cs = (cs + data[i]) % 0xFF;
	}

	tmpmsg[len+4] = cs;

	//Send message
	socklen_t client_len = sizeof(client);
	if(sendto(sock,tmpmsg, len+5, 0,(struct sockaddr *) &client, client_len) < 0 )
	{
		log_error("Sending messages failed");
		close(sock);
		free (tmpmsg);
		return;
	}

	// log_debug("send succeded");

	// print sent data
	char *tx = (char *)malloc(sizeof (char) * (len+5) * 2 + 5);
	tx[0] = 'T';
	tx[1] = 'X';
	tx[2] = ':';
	tx[3] = ' ';

	for(int i=0; i<(len+5); i++)
	{
		tx[2 * i + 1 + 4] 	= net_hex_to_char(tmpmsg[i]);
		tx[2 * i     + 4]	= net_hex_to_char(tmpmsg[i] >> 4);
	}

	tx[2*(len+5) + 4] = '\0';
	gui_log(CON_COM, tx);
	free(tx);

	close(sock);
	free (tmpmsg);
}

void net_senderror(void* psenderinfo, module_id_t module_id, error_code_t error_code, uint16_t plen, uint8_t data[])
{
	int sock;
	struct sockaddr_in client;

	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(DEST_PORT);
	pnetsenderinfo_t senderinfo = (pnetsenderinfo_t) psenderinfo;

	if(!inet_aton(senderinfo->net_address, &client.sin_addr))
	{
		log_error("The net adress is not valid ");
		return;
	}

	if((sock=socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		log_error("Unable to create sending socket");
		return;
	}

	//Calculate len data part
	uint16_t len = 4 + plen;

	//Build message
	char* tmpmsg = (char*) malloc(sizeof(char)*(len+5));
	tmpmsg[0] = (char) 0xFF;
	tmpmsg[1] = (char) 0xFF;
	tmpmsg[2] = char((uint8_t) (len>>8));
	tmpmsg[3] = char((uint8_t) len);
	tmpmsg[4] = char((uint8_t) (senderinfo->fc>>8));
	tmpmsg[5] = char((uint8_t) senderinfo->fc);
	tmpmsg[6] = char((uint8_t) module_id);
	tmpmsg[7] = char((uint8_t) error_code);

	//Calculate Checksum
	uint8_t cs = 0;

	for(int i=0; i<8; i++)
	{
		cs = (cs + tmpmsg[i]) % 0xFF;
	}

	for(int i=0; i<len-4; i++)
	{
		tmpmsg[i+8] = data[i];
		cs = (cs + data[i]) % 0xFF;
	}
	tmpmsg[len+4] = cs;

	//send message
	socklen_t client_len = sizeof(client);
	if(sendto(sock,tmpmsg, len+5, 0,(struct sockaddr *) &client, client_len) < 0 )
	{
		log_error("Sending messages failed");
		close(sock);
		free (tmpmsg);
		return;
	}

	//print sent data
	char *tx = (char *)malloc(sizeof (char) * (len+5) * 2 + 5);
	tx[0] = 'T';
	tx[1] = 'X';
	tx[2] = ':';
	tx[3] = ' ';
	for(int i=0 ; i<(len+5); i++)
	{
		tx[2 * i + 1 + 4] 	= net_hex_to_char(tmpmsg[i]);
		tx[2 * i     + 4] 	= net_hex_to_char(tmpmsg[i] >> 4);
	}

	tx[2*(len+5) + 4] = '\0';
	gui_log(CON_COM, tx);
	free(tx);

	close(sock);
	free (tmpmsg);
}

////////////////////////////////////////////////////////////////////////////////
// private function implementation

void *net_run_thread(void *ptr)
{
	char socket_buffer[NET_BUFSIZE];
	socklen_t socklen = sizeof(struct sockaddr_in);

	netsenderinfo_t senderinfo;
	sockaddr_in sender;
	for(;;)
	{
		// receive data
		ssize_t len = recvfrom(rxSocket, socket_buffer, NET_BUFSIZE, 0, (struct sockaddr*) &sender, &socklen);
		net_buffer_add_range(buffer, len, (uint8_t *) socket_buffer);

		// print received data
		char *rx = (char *)malloc(sizeof (char) * len * 2 + 5);
		rx[0] = 'R';
		rx[1] = 'X';
		rx[2] = ':';
		rx[3] = ' ';
		for(int i=0 ; i<len; i++)
		{
			rx[2 * i + 1 + 4] 	= net_hex_to_char(socket_buffer[i]);
			rx[2 * i     + 4] 	= net_hex_to_char(socket_buffer[i] >> 4);
		}

		rx[2*len + 4] = '\0';
		gui_log(CON_COM, rx);
		free(rx);

		// decode message
		uint16_t bufLen;
		while((bufLen = net_buffer_count(buffer)) >= 5)
		{
			uint16_t fc  = net_buffer_get(buffer, 0) << 8 | net_buffer_get(buffer, 1),
				  msglen = net_buffer_get(buffer, 2) << 8 | net_buffer_get(buffer, 3);

			// assign sender info
			senderinfo.net_address = inet_ntoa(sender.sin_addr);
			senderinfo.fc = fc;

			if(fc != 0 && fc - 1 < interpreterCount)
			{
				if(msglen + 5 > bufLen) // incomplete message .. wait for next receive
				{
					DEBUG("Incomplete Message.. wait for more ...");
					break;
				}
				else
				{
					if(	(msglen < tblInterpreter[fc - 1].len_min) ||
						(tblInterpreter[fc - 1].len_max != 0xFFFF &&
						 msglen > tblInterpreter[fc - 1].len_max) )
					{
						DEBUG("Wrong message length. Discard message.");
					}
					else if(!net_check_cs(msglen))
					{
						DEBUG("Received message with wrong checksum. Discard message");
					}
					else
					{
						if(tblInterpreter[fc - 1].callback == NULL)
						{
							DEBUG("Unable to forward reveived message. No callback function available. Discard Message.");
						}
						else
						{
							uint8_t *tempData = (uint8_t *) malloc(sizeof(uint8_t) * msglen);
							if(tempData == NULL)
							{
								DEBUG("Unable to allocate memory for forwarding the received message.Discard Message.");
							}
							else
							{
								for(int i=0 ; i<msglen ; i++)
									tempData[i] = net_buffer_get(buffer, i + 4);
								// void (*function) (void*, uint16_t, uint16_t, uint8_t*)= tblInterpreter[fc - 1].callback;
								jobstack_addjob(senderinfo, fc, msglen, tempData, tblInterpreter[fc - 1].callback);
							}
						}
					}

					net_buffer_remove_range(buffer, msglen + 5);
				}
			}
			else // unknown function code
			{
				net_buffer_remove(buffer);
				DEBUG("Received unknown fc: %04x: Bytes left in Buffer: %d", fc, net_buffer_count(buffer));
			}
		}
	}
}

bool net_check_cs(uint16_t len)
{
	uint8_t cs = 0;
	for(uint16_t i=0 ; i<len + 4 ; i++)
		cs = (cs + net_buffer_get(buffer, i)) % 0xFF;

	return cs == net_buffer_get(buffer, len + 4);
}

char net_hex_to_char(uint8_t byte)
{
	byte = byte & 0x0F;
	return (char)(byte > 9 ? byte + 0x37 : byte + 0x30);
}
