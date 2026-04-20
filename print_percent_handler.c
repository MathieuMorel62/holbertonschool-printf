#include "main.h"

/**
 * print_pct - prints the '%' character
 * @ap: argument list (unused)
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int print_pct(va_list ap __attribute__((unused)), print_buffer_t *pb)
{
	if (pb_putc(pb, '%') < 0)
		return (-1);
	return (1);
}
