#include "main.h"

/**
 * reset_format_flags - reset flags before reading one conversion
 * @pb: output buffer and formatting state
 *
 * Return: nothing
 */
static void reset_format_flags(print_buffer_t *pb)
{
	pb->flag_plus = 0;
	pb->flag_space = 0;
	pb->flag_hash = 0;
	pb->conversion_specifier = '\0';
}

/**
 * parse_flags - parse +, space and # flags
 * @format: format string
 * @pi: current index in format string
 * @pb: output buffer and formatting state
 *
 * Return: 0 on success, -2 if format ends after flags
 */
static int parse_flags(const char *format, int *pi, print_buffer_t *pb)
{
	while (format[*pi] == '+' || format[*pi] == ' ' || format[*pi] == '#')
	{
		if (format[*pi] == '+')
			pb->flag_plus = 1;
		else if (format[*pi] == ' ')
			pb->flag_space = 1;
		else
			pb->flag_hash = 1;
		*pi = *pi + 1;
	}
	if (format[*pi] == '\0')
		return (-2);
	return (0);
}

/**
 * apply_specifier - handle one '%' conversion
 * @format: format string
 * @pi: index of '%'; updated after processing
 * @plen: running length; updated
 * @ap: variadic arguments
 * @pb: output buffer
 *
 * Return: 0 on success, -1 on I/O error, -2 on invalid format
 */
static int apply_specifier(const char *format, int *pi, int *plen,
		va_list ap, print_buffer_t *pb)
{
	int i;
	int len;
	int result;
	int (*func)(va_list ap, print_buffer_t *pb);

	i = *pi + 1;
	len = *plen;
	reset_format_flags(pb);
	if (parse_flags(format, &i, pb) < 0)
		return (-2);
	pb->conversion_specifier = format[i];
	func = get_function(format + i);
	if (func == NULL)
	{
		if (pb_putc(pb, '%') < 0 || pb_putc(pb, format[i]) < 0)
			return (-1);
		len = len + 2;
	}
	else
	{
		result = func(ap, pb);
		if (result < 0)
			return (-1);
		len = len + result;
	}
	*pi = i + 1;
	*plen = len;
	return (0);
}

/**
 * write_regular_char - write one non-format character
 * @format: format string
 * @pi: current index, updated by one
 * @plen: printed length, updated by one
 * @pb: output buffer
 *
 * Return: 0 on success, -1 on I/O error
 */
static int write_regular_char(const char *format, int *pi, int *plen,
		print_buffer_t *pb)
{
	if (pb_putc(pb, format[*pi]) < 0)
		return (-1);
	*pi = *pi + 1;
	*plen = *plen + 1;
	return (0);
}

/**
 * _printf - function printf
 * @format: character string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	int i;
	int len;
	int result;
	va_list ap;
	print_buffer_t pb;

	i = 0;
	len = 0;
	pb.used = 0;
	reset_format_flags(&pb);
	va_start(ap, format);
	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (va_end(ap), -1);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			result = apply_specifier(format, &i, &len, ap, &pb);
			if (result < 0)
				return ((void)pb_flush(&pb), va_end(ap), -1);
		}
		else if (write_regular_char(format, &i, &len, &pb) < 0)
			return ((void)pb_flush(&pb), va_end(ap), -1);
	}
	if (pb_flush(&pb) < 0)
		return (va_end(ap), -1);
	va_end(ap);
	return (len);
}
