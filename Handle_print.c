#include "main.h"
/**
 * handle_print - Prints an argument based on type
 * @list: List of arguments to be printed
 * @flags: Determines active flags
 * @fmt: Formatted string in which to print the arguments
 * @ind: ind
 * @buffer: Buffer array to store print
 * @precision: Precision specs
 * @flags: Determines active flags
 * @size: Size specifier
 * @width: determine width
 * Return: 1 or 2
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{

	int j = 0, unknown = 0;
	fmt_t frmtype[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	while (frmtype[j].fmt != '\0' && fmt[*ind] != frmtype[j].fmt)
		j++;
	if (frmtype[j].fmt != '\0')
		return (frmtype[j].fn(list, buffer, flags, width, precision, size));
	if (fmt[*ind] == '\0')
		return (-1);
	if (fmt[*ind - 1] == ' ')
	{
		if (fmt[*ind - 1] == ' ')
			unknown += write(1, &fmt[*ind], 1);
	}
	else if (width)
	{
		(*ind)--;
		while (fmt[*ind] != ' ' && fmt[*ind] != '%')
			(*ind)--;
		if (fmt[*ind] == ' ')
			(*ind)--;
		return (1);
	}
	else
	{
		unknown += write(1, "%%", 1);
		unknown += write(1, &fmt[*ind], 1);
	}
	return (unknown);
}
