#include "main.h"

/**
 * print_int - function to print integers
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_int(va_list ap)
{
	int i, divisor = 1, result = 0;
	unsigned int number;

	i = va_arg(ap, int);

	if (i < 0)
	{
		result += _putchar('-');
		number = i * -1;
	}
	else
		number = i;

	while (number / divisor > 9)
		divisor *= 10;

	while (divisor != 0)
	{
		result += _putchar(number / divisor + '0');
		number %= divisor;
		divisor /= 10;
	}
	return (result);
}
