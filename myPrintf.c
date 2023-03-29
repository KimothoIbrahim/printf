#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

/**
 * converter - tun integers to string
 * @number: argument to convert
 * @buffer: string changed
 *
 * Return: nothing
 */

void converter(uint64_t number, int base, char *buffer)
{
	int i, j, current = 0, digit;
	char buff[65];

	if (number == 0)
	{
		*buffer++ = '0';
		*buffer = 0;
		return;
	}

	for (i = 0; i < 65; i++)
		buff[i] = 0;

	while (number)
	{
		digit = number % base;
		if (digit >= 10)
			buff[current++] = 'a' + (digit + 10);
		else
			buff[current++] = '0' + digit;

		number /= base;
	}

	for (j = current - 1; j != 0; j--)
		*buffer++ = buff[j];
	*buffer++ = buff[0];
	*buffer = 0;
}

void negatives(int64_t number, int base, char *buffer)
{
	if (number < 0)
	{
		*buffer++ = '-';
		number = -number;
	}

	converter(number, base, buffer);

}

/**
 * _printf - mimics stdlib printf function
 * @format: string literal parameter for formating and
 * including subsequent arguments
 *
 * Return: returns number of characters printed
 */
int _printf(const char *format, ...)
{	int i, u, v, x = 0, d, ii, r;
	char c, *s, buffer[27];
	void *f;
	char per = '%';
	va_list ap;

	va_start(ap, format);
	
	for (i = 0; *(format + i); i++)
	{
		if (*(format + i) == '%')
		{
			if (*(format + i + 1) == 'd')
			{
				d = va_arg(ap, int);
				negatives(d, 10, buffer);
				for (u = 0; buffer[u]; u++)
				{
					x += write(1, buffer + u, 1);
				}

				format++;
			}

			if (*format + i + 1 == '%')
			{
				x += write(1, &per, 1);
				format++;
			}

			if (*(format + i + 1) == 'c')
			{
				c = (char) va_arg(ap, int);
				x += write(1, &c, 1);
				format++;
			}
			if (*(format + i + 1) == 's')
			{
				s = va_arg(ap, char *);
				while (*s)
				{
					x += write(1, s++, 1);
				}
				format++;
			}
			if (*(format + i + 1) == 'i')
			{
				ii = va_arg(ap, int);
				converter(ii, 10, buffer);
				for (v = 0; buffer[v]; v++)
				{
					x += write(1, buffer + v, 1);
				}
				format++;
			}
			if (*(format + i + 1) == 'x')
			{
				r = va_arg(ap, int);
				converter(r, 16, buffer);
				for (v = 0; buffer[v]; v++)
				{
					x += write(1, buffer + v, 1);
				}
				format++;
			}
			if (*(format + i + 1) == 'p')
			{
				f = va_arg(ap, void *);
				converter((int64_t) f, 16, buffer);
				for (v = 0; buffer[v]; v++)
				{
					x += write(1, buffer + v, 1);
				}
				format++;
			}
		}
		else
		{
			x += write(1, format + i, 1);
		}
	}

	va_end(ap);

	return (x);
}
