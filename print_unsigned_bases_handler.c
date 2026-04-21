#include "main.h"

/**
 * print_unsigned - print unsigned int
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_unsigned(va_list ap, print_buffer_t *pb)
{
	unsigned long n;
	unsigned long divisor;
	unsigned long digit;
	int result;

	n = get_unsigned_value_from_args(ap, pb);
	divisor = 1;
	result = 0;

	if (n == 0)
	{
		if (pb_putc(pb, '0') < 0)
			return (-1);
		return (1);
	}

	while ((n / divisor) > 9)
		divisor = divisor * 10;

	while (divisor != 0)
	{
		digit = n / divisor;
		if (pb_putc(pb, (char)(digit + '0')) < 0)
			return (-1);
		result = result + 1;
		n = n % divisor;
		divisor = divisor / 10;
	}

	return (result);
}


/**
 * print_octal - print unsigned int in octal
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_octal(va_list ap, print_buffer_t *pb)
{
	unsigned long n;
	unsigned long original_value;
	char buf[32];
	int size;
	int len_digits;
	int len_prefix;

	n = get_unsigned_value_from_args(ap, pb);
	original_value = n;
	size = 0;

	if (n == 0)
	{
		if (pb_putc(pb, '0') < 0)
			return (-1);
		return (1);
	}

	while (n != 0)
	{
		buf[size] = (char)((n % 8) + '0');
		n = n / 8;
		size = size + 1;
	}
	len_prefix = 0;
	if (pb->flag_hash == 1 && original_value != 0)
	{
		if (pb_putc(pb, '0') < 0)
			return (-1);
		len_prefix = 1;
	}
	len_digits = write_reversed_buffer(pb, buf, size);
	if (len_digits < 0)
		return (-1);
	return (len_prefix + len_digits);
}

/**
 * print_hex - print unsigned int in hexadecimal
 * @ap: argument list
 * @digits: symbols used for conversion
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
static int print_hex(va_list ap, const char *digits, print_buffer_t *pb)
{
	unsigned long n;
	unsigned long original_value;
	char buf[16];
	int size;
	int len_digits;
	int len_prefix;

	n = get_unsigned_value_from_args(ap, pb);
	original_value = n;
	size = 0;

	if (n == 0)
	{
		if (pb_putc(pb, '0') < 0)
			return (-1);
		return (1);
	}

	while (n != 0)
	{
		buf[size] = digits[n % 16];
		n = n / 16;
		size = size + 1;
	}
	len_prefix = write_hex_prefix_if_needed(pb, original_value);
	if (len_prefix < 0)
		return (-1);
	len_digits = write_reversed_buffer(pb, buf, size);
	if (len_digits < 0)
		return (-1);
	return (len_prefix + len_digits);
}

/**
 * print_hex_lower - print unsigned int in hexadecimal lowercase
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_hex_lower(va_list ap, print_buffer_t *pb)
{
	return (print_hex(ap, "0123456789abcdef", pb));
}

/**
 * print_hex_upper - print unsigned int in hexadecimal uppercase
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_hex_upper(va_list ap, print_buffer_t *pb)
{
	return (print_hex(ap, "0123456789ABCDEF", pb));
}
