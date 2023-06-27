#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: chars printed
 */

int _printf(const char *format, ...)
{

	int flags, width, precision, size, buff_ind = 0;
	int j = 0, ptd = 0, printed_chars = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	while (format && format[j] != '\0')
	{
		if (format[j] != '%')
		{
			buffer[buff_ind++] = format[j];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &j);
			width = get_width(format, &j, list);
			precision = get_precision(format, &j, list);
			size = get_size(format, &j);
			++j;
			ptd = handle_print(format, &j, list, buffer,
					flags, width, precision, size);
			if (ptd == -1)
				return (-1);
			printed_chars += ptd;
		}
		j++;
	}
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: Array of chars with characters to be printed
 * @buff_ind: Pointer to an integer with number of characters
 */

void print_buffer(char buffer[], int *buff_ind)
{

	int i = 0;

	while (i < *buff_ind)
	{
		write(1, &buffer[i], 1);
		i++;
	}
	*buff_ind = 0;
}
