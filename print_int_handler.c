#include "main.h"

/**
 * write_positive_int_sign - handle '+' and ' ' flags
 * @pb: output buffer
 *
 * Return: number of sign chars written, or -1 on error
 */
static int write_positive_int_sign(print_buffer_t *pb)
{
	if (pb->conversion_specifier != 'd' && pb->conversion_specifier != 'i')
		return (0);
	if (pb->flag_plus == 1)
	{
		if (pb_putc(pb, '+') < 0)
			return (-1);
		return (1);
	}
	if (pb->flag_space == 1)
	{
		if (pb_putc(pb, ' ') < 0)
			return (-1);
		return (1);
	}
	return (0);
}

/**
 * write_unsigned_decimal - print decimal digits from unsigned value
 * @pb: output buffer
 * @magnitude: unsigned value to print
 *
 * Return: number of characters printed, or -1 on error
 */
static int write_unsigned_decimal(print_buffer_t *pb, unsigned int magnitude)
{
	int divisor;
	int char_to_print;
	int count;

	divisor = 1;
	while ((magnitude / divisor) > 9)
		divisor = divisor * 10;
	count = 0;
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
	int count;
	int result;

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
	{
		result = write_positive_int_sign(pb);
		if (result < 0)
			return (-1);
		count = count + result;
		magnitude = (unsigned int)value;
	}
	result = write_unsigned_decimal(pb, magnitude);
	if (result < 0)
		return (-1);
	count = count + result;
	return (count);
}
