#include "main.h"

/**
 * print_int - print a signed integer in decimal
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_int(va_list ap, print_buffer_t *pb)
{
	int value;
	unsigned int magnitude;
	int divisor;
	int char_to_print;
	int count;

	value = va_arg(ap, int);
	count = 0;

	if (value < 0)
	{
		if (pb_putc(pb, '-') < 0)
			return (-1);
		count = count + 1;
		magnitude = (unsigned int)(-(long)value);
	}
	else
		magnitude = (unsigned int)value;

	divisor = 1;
	while ((magnitude / divisor) > 9)
		divisor = divisor * 10;

	while (divisor != 0)
	{
		char_to_print = (int)(magnitude / divisor) + (int)'0';
		if (pb_putc(pb, (char)char_to_print) < 0)
			return (-1);
		count = count + 1;
		magnitude = magnitude % divisor;
		divisor = divisor / 10;
	}

	return (count);
}
