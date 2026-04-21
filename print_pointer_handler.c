#include "main.h"

/**
 * write_pointer_prefix_and_null - write "0x" and handle null pointer
 * @pb: output buffer
 * @pointer_value: pointer value cast to uintptr_t
 *
 * Return: 3 if null handled ("0x0"), 2 if only prefix written, -1 on error
 */
static int write_pointer_prefix_and_null(print_buffer_t *pb,
		uintptr_t pointer_value)
{
	if (pb_putc(pb, '0') < 0)
		return (-1);

	if (pb_putc(pb, 'x') < 0)
		return (-1);

	if (pointer_value == 0)
	{
		if (pb_putc(pb, '0') < 0)
			return (-1);

		return (3);
	}

	return (2);
}

/**
 * write_pointer_hex_digits - write hexadecimal digits for pointer value
 * @pb: output buffer
 * @pointer_value: pointer value cast to uintptr_t
 *
 * Return: number of hex digits written, or -1 on error
 */
static int write_pointer_hex_digits(print_buffer_t *pb,
		uintptr_t pointer_value)
{
	uintptr_t temp_value;
	char hex_buffer[sizeof(uintptr_t) * 2];
	const char *hex_digits;
	int i;
	int count;

	hex_digits = "0123456789abcdef";
	temp_value = pointer_value;
	i = 0;

	while (temp_value != 0)
	{
		hex_buffer[i] = hex_digits[temp_value % 16];
		temp_value /= 16;
		i++;
	}

	count = 0;
	while (i > 0)
	{
		i--;
		if (pb_putc(pb, hex_buffer[i]) < 0)
			return (-1);
		count++;
	}

	return (count);
}

/**
 * print_pointer - print an address in hexadecimal with 0x prefix
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_pointer(va_list ap, print_buffer_t *pb)
{
	uintptr_t pointer_value;
	int prefix_result;
	int digits_result;

	pointer_value = (uintptr_t)va_arg(ap, void *);

	prefix_result = write_pointer_prefix_and_null(pb, pointer_value);
	if (prefix_result < 0)
		return (-1);

	if (prefix_result == 3)
		return (prefix_result);

	digits_result = write_pointer_hex_digits(pb, pointer_value);
	if (digits_result < 0)
		return (-1);

	return (prefix_result + digits_result);
}
