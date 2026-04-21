#include "main.h"

/**
 * write_reversed_buffer - print reversed temporary digits buffer
 * @pb: output buffer
 * @buf: temporary digits buffer
 * @size: number of valid chars in buf
 *
 * Return: number of characters printed, or -1 on error
 */
int write_reversed_buffer(print_buffer_t *pb, char *buf, int size)
{
	int len;

	len = 0;
	while (size > 0)
	{
		size = size - 1;
		if (pb_putc(pb, buf[size]) < 0)
			return (-1);
		len = len + 1;
	}
	return (len);
}

/**
 * write_hex_prefix_if_needed - print 0x/0X prefix for # flag
 * @pb: output buffer
 * @original_value: original numeric value
 *
 * Return: prefix length, 0 when not printed, or -1 on error
 */
int write_hex_prefix_if_needed(print_buffer_t *pb,
	unsigned long original_value)
{
	if (pb->flag_hash != 1 || original_value == 0)
		return (0);
	if (pb->conversion_specifier == 'x')
	{
		if (pb_putc(pb, '0') < 0 || pb_putc(pb, 'x') < 0)
			return (-1);
		return (2);
	}
	if (pb->conversion_specifier == 'X')
	{
		if (pb_putc(pb, '0') < 0 || pb_putc(pb, 'X') < 0)
			return (-1);
		return (2);
	}
	return (0);
}

/**
 * get_unsigned_value_from_args - read unsigned val with optional h/l modifier
 * @ap: argument list
 * @pb: formatting state
 *
 * Return: unsigned value converted according to length modifier
 */
unsigned long get_unsigned_value_from_args(va_list ap, print_buffer_t *pb)
{
	unsigned long value;

	if (pb->length_modifier == 'l')
		value = va_arg(ap, unsigned long);
	else
	{
		value = (unsigned long)va_arg(ap, unsigned int);
		if (pb->length_modifier == 'h')
			value = (unsigned long)((unsigned short)value);
	}
	return (value);
}
