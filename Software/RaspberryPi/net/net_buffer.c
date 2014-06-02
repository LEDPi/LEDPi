#include "net/net_buffer.h"

pnetbuffer_t net_buffer_create(uint16_t max_len)
{
	pnetbuffer_t buffer = (pnetbuffer_t) malloc(sizeof(netbuffer_t));
	buffer->writePos = 0;
	buffer->readPos = 0;
	buffer->maxLen = max_len;
	buffer->buffer = (uint8_t *) malloc(sizeof(uint8_t) * max_len);

	return buffer;
}

void net_buffer_delete(pnetbuffer_t buffer)
{
	free(buffer->buffer);
	free(buffer);
}

void net_buffer_add_range(pnetbuffer_t buffer, uint8_t len, uint8_t data[])
{
	for(int i=0 ; i<len ; i++)
		buffer->buffer[(buffer->writePos + i) % buffer->maxLen] = data[i];

	buffer->writePos = (buffer->writePos + len) % buffer->maxLen;
}

void net_buffer_add(pnetbuffer_t buffer, uint8_t data)
{
	buffer->buffer[buffer->writePos] = data;
	buffer->writePos = ++buffer->writePos % buffer->maxLen;
}

void net_buffer_remove(pnetbuffer_t buffer)
{
	if(net_buffer_count(buffer) == 0)
	{
	    log_error("Unable to remove byte from empty buffer.");
	}
	else
	{
		buffer->readPos = ++buffer->readPos % buffer->maxLen;
	}
}

void net_buffer_remove_range(pnetbuffer_t buffer, uint8_t len)
{
	if(net_buffer_count(buffer) < len)
	{
        log_error("Unable to remove byte from buffer.(%d in Buffer [%d])", net_buffer_count(buffer), len);
	}
	else
	{
		buffer->readPos = (buffer->readPos + len) % buffer->maxLen;
    }
}

uint8_t net_buffer_get(pnetbuffer_t buffer, int index)
{
	return buffer->buffer[(buffer->readPos + index) % buffer->maxLen];
}

uint16_t net_buffer_count(pnetbuffer_t buffer)
{
	return buffer->readPos <= buffer->writePos ?
		buffer->writePos - buffer->readPos :
		buffer->maxLen - buffer->readPos + buffer->writePos;
}
