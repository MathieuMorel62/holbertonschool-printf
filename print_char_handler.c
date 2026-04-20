#include "main.h"

/**
 * print_char - print a single character
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_char(va_list ap)
{
	_putchar(va_arg(ap, int));
	return (1);
}
