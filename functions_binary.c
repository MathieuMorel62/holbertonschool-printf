#include "main.h"

/**
 * convert_binary - convert unsigned int in binary
 * @ap: argument list
 * @pb: output buffer
 *
 * Return: number of characters printed, or -1 on error
 */
int convert_binary(va_list ap, print_buffer_t *pb)
{
	unsigned int n, max, i, sum;
	unsigned int bin[32];
	int len;

	n = va_arg(ap, unsigned int);
	max = 2147483648;
	bin[0] = n / max;
	for (i = 1; i < 32; i++)
	{
		max = max / 2;
		bin[i] = (n / max) % 2;
	}
	sum = 0;
	len = 0;
	for (i = 0; i < 32; i++)
	{
		sum = sum + bin[i];
		if (sum != 0 || i == 31)
		{
			if (pb_putc(pb, (char)('0' + bin[i])) < 0)
				return (-1);
			len = len + 1;
		}
	}
	return (len);
}
