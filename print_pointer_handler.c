#include "main.h"

/**
 * write_pointer_nil - write "(nil)" for null pointer
 * @pb: output buffer
 *
 * Return: 5 on success, -1 on error
 */
static int write_pointer_nil(print_buffer_t *pb)
{
	if (pb_putc(pb, '(') < 0)
		return (-1);
	if (pb_putc(pb, 'n') < 0)
		return (-1);
	if (pb_putc(pb, 'i') < 0)
		return (-1);
	if (pb_putc(pb, 'l') < 0)
		return (-1);
	if (pb_putc(pb, ')') < 0)
		return (-1);

	return (5);
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
	int digits_result;

	pointer_value = (uintptr_t)va_arg(ap, void *);

	if (pointer_value == 0)
		return (write_pointer_nil(pb));

	if (pb_putc(pb, '0') < 0)
		return (-1);
	if (pb_putc(pb, 'x') < 0)
		return (-1);

	digits_result = write_pointer_hex_digits(pb, pointer_value);
	if (digits_result < 0)
		return (-1);

	return (digits_result + 2);
}
