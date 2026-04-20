#include "main.h"

#define PRINT_BUFFER_CAPACITY 1024

/**
 * pb_flush - write all pending bytes in the buffer to stdout
 * @pb: output buffer
 *
 * Return: 0 on success, -1 on write error
 */
int pb_flush(print_buffer_t *pb)
{
	ssize_t written_bytes;
	int bytes_left_to_write;
	char *write_position;

	if (pb->used == 0)
		return (0);

	bytes_left_to_write = pb->used;
	write_position = pb->buf;

	while (bytes_left_to_write > 0)
	{
		written_bytes = write(1, write_position, (size_t)bytes_left_to_write);
		if (written_bytes <= 0)
			return (-1);
		write_position = write_position + written_bytes;
		bytes_left_to_write = bytes_left_to_write - (int)written_bytes;
	}

	pb->used = 0;
	return (0);
}

/**
 * pb_putc - append one character; flush when buffer is full
 * @pb: output buffer
 * @c: character to append
 *
 * Return: 0 on success, -1 on error
 */
int pb_putc(print_buffer_t *pb, char c)
{
	if (pb->used == PRINT_BUFFER_CAPACITY)
	{
		if (pb_flush(pb) < 0)
			return (-1);
	}

	pb->buf[pb->used] = c;
	pb->used = pb->used + 1;
	return (0);
}
