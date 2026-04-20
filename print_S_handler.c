#include "main.h"

/**
 * print_string_custom_S - %S: string with non-printables as \xHH (uppercase)
 * @ap: argument list (char *)
 * @pb: output buffer
 *
 * Return: number of characters written to pb, or -1 on error
 */
int print_string_custom_S(va_list ap, print_buffer_t *pb)
{
	char *str;
	int i;
	int count;
	unsigned char c;
	static const char hex_digits[] = "0123456789ABCDEF";

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";

	count = 0;
	i = 0;

	while (str[i] != '\0')
	{
		c = str[i];

		if ((c < 32 && c > 0) || c >= 127)
		{
			if (pb_putc(pb, '\\') < 0 || pb_putc(pb, 'x') < 0 ||
			    pb_putc(pb, hex_digits[c / 16]) < 0 ||
			    pb_putc(pb, hex_digits[c % 16]) < 0)
				return (-1);
			count += 4;
		}
		else
		{
			if (pb_putc(pb, c) < 0)
				return (-1);
			count++;
		}
		i++;
	}

	return (count);
}
