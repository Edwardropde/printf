#include "main.h"
/**
 * print_unsigned - Prints unsigned number
 * @arglist: List of arguments
 * @width: get width
 * @buffer: Buffer array managing print
 * @flags:  Calculates active flags
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_unsigned(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(arglist, unsigned long int);

	number = convert_size_unsgnd(number, size);
	if (number == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	for (; number > 0; number /= 10)
		buffer[j--] = (number % 10) + '0';
	j++;
	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints unsigned number in octal notation
 * @arglist: List of arguments
 * @width: get width
 * @buffer: Buffer array managing print
 * @flags:  Calculates active flags
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */

int print_octal(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(arglist, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);
	number = convert_size_unsgnd(number, size);
	if (number == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	for (; number > 0; number /= 8)
	{
		buffer[j--] = (number % 8) + '0';
	}
	if (flags & F_HASH && init_number != 0)
		buffer[j--] = '0';
	return (write_unsgnd(0, j + 1, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints unsigned number in hexadecimal notation
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	return (print_hexa(arglist, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints unsigned number in upper hexadecimal notation
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @precision: Precision specification
 * @buffer: Buffer array managing print
 * @width: get width
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_hexa_upper(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	return (print_hexa(arglist, "0123456789ABCDEF", buffer,
			flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints hexadecimal number in upper or lower
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @precision: Precision specification
 * @mapval: Array of values to map digits to
 * @chflag: Active flags
 * @buffer: Buffer array managing print
 * @width: get width
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_hexa(va_list arglist, char mapval[], char buffer[],
	int flags, char chflag, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int number = va_arg(arglist, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);
	if (number == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	for (; number > 0; number /= 16)
	{
		buffer[j--] = mapval[number % 16];
	}
	if (flags & F_HASH && init_number != 0)
	{
		buffer[j--] = chflag;
		buffer[j--] = '0';
	}
	j++;
	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}
