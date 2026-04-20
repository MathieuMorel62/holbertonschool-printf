#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * struct print_buffer - local output buffer for _printf
 * @buf: character storage (1024 bytes)
 * @used: number of valid bytes in buf
 */
typedef struct print_buffer
{
	char buf[1024];
	int used;
} print_buffer_t;

/**
 * struct print - type structure
 * @parameter: argument pointer
 * @f: pointer function to argument
 */

typedef struct print
{
	char *parameter;
	int (*f)(va_list ap, print_buffer_t *pb);
} print_type;

/* different prototypes */

int _printf(const char *format, ...);
int _putchar(char c);
int pb_putc(print_buffer_t *pb, char c);
int pb_flush(print_buffer_t *pb);
int print_char(va_list ap, print_buffer_t *pb);
int print_string(va_list ap, print_buffer_t *pb);
int print_pct(va_list ap, print_buffer_t *pb);
int print_int(va_list ap, print_buffer_t *pb);
int convert_binary(va_list ap, print_buffer_t *pb);
int (*get_function(const char *format))(va_list, print_buffer_t *);
int print_unsigned(va_list ap, print_buffer_t *pb);
int print_octal(va_list ap, print_buffer_t *pb);
int print_hex_lower(va_list ap, print_buffer_t *pb);
int print_hex_upper(va_list ap, print_buffer_t *pb);
int print_string_custom_S(va_list ap, print_buffer_t *pb);

#endif
