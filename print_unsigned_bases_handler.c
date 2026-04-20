#include "main.h"

/**
 * print_unsigned - print unsigned int
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list ap)
{
	unsigned int n;
	unsigned int divisor;
	unsigned int digit;
	int result;

	n = va_arg(ap, unsigned int);
	divisor = 1;
	result = 0;

	if (n == 0)
		return (_putchar('0'));

	while ((n / divisor) > 9)
		divisor *= 10;

	while (divisor != 0)
	{
		digit = n / divisor;
		result += _putchar(digit + '0');
		n %= divisor;
		divisor /= 10;
	}

	return (result);
}


/**
 * print_octal - print unsigned int in octal
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_octal(va_list ap)
{
	unsigned int n;
	char buf[32];
	int i;
	int len;

	n = va_arg(ap, unsigned int);
	i = 0;
	len = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n != 0)
	{
		buf[i] = (n % 8) + '0';
		n /= 8;
		i++;
	}

	while (i > 0)
	{
		len += _putchar(buf[--i]);
	}

	return (len);
}

/**
 * print_hex - print unsigned int in hexadecimal
 * @ap: argument list
 * @digits: symbols used for conversion
 *
 * Return: number of characters printed
 */
static int print_hex(va_list ap, const char *digits)
{
	unsigned int n;
	char buf[16];
	int i;
	int len;

	n = va_arg(ap, unsigned int);
	i = 0;
	len = 0;

	if (n == 0)
		return (_putchar('0'));

	while (n != 0)
	{
		buf[i] = digits[n % 16];
		n /= 16;
		i++;
	}

	while (i > 0)
		len += _putchar(buf[--i]);

	return (len);
}

/**
 * print_hex_lower - print unsigned int in hexadecimal lowercase
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list ap)
{
	return (print_hex(ap, "0123456789abcdef"));
}

/**
 * print_hex_upper - print unsigned int in hexadecimal uppercase
 * @ap: argument list
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list ap)
{
	return (print_hex(ap, "0123456789ABCDEF"));
}
