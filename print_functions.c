#include "main.h"
/**
 * print_char - Prints character
 * @buffer: Buffer array managing print
 * @arglist: List of arguments
 * @width: Width
 * @flags:  Calculates active flags
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_char(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	char k = va_arg(arglist, int);

	return (handle_write_char(k, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @arglist: List of arguments
 * @buffer: Buffer array managing print
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * @width: get width.
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	int lgth = 0, j;
	char *str = va_arg(arglist, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[lgth] != '\0')
		lgth++;
	if (precision >= 0 && precision < lgth)
		lgth = precision;
	if (width > lgth)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lgth);
			for (j = width - lgth; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - lgth; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], lgth);
			return (width);
		}
	}
	for (j = 0; j < lgth; j++)
		write(1, &str[j], 1);
	return (lgth);
}

/**
 * print_percent - Prints percent sign
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array managing print
 * @width: get width.
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */

int print_percent(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	UNUSED(arglist);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @arglist: List of arguments
 * @flags: Calculates active flags
 * @buffer: Buffer array managing print
 * @width: Get width.
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of chars printed
 */

int print_int(va_list arglist, char buffer[],
	int flags, int width, int precision, int size)
{

	int thenegative = 0;
	int j = BUFF_SIZE - 2;
	long int nnumb = va_arg(arglist, long int);
	unsigned long int dig;

	nnumb = convert_size_number(nnumb, size);
	if (nnumb == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	dig = (unsigned long int)nnumb;
	if (nnumb < 0)
	{
		dig = (unsigned long int)((-1) * nnumb);
		thenegative = 1;
	}
	for (; dig > 0; dig /= 10)
	{
		buffer[j--] = (dig % 10) + '0';
	}
	j++;
	return (write_number(thenegative, j, buffer, flags,
				width, precision, size));
}

/**
 * print_binary - Prints unsigned number
 * @arglist: List of arguments
 * @width: Width specifier
 * @buffer: Buffer array managing print
 * @flags: Calculates active flags
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Number of characters printed
 */

int print_binary(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	unsigned int b[32];
	unsigned int nnumb, m, j, total;
	int count;

	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(width);
	UNUSED(flags);

	nnumb = va_arg(arglist, unsigned int);
	m = 2147483648;
	for (j = 0; j < 32; j++)
	{
		b[j] = (nnumb & m) ? 1 : 0;
		m >>= 1;
	}
	j = 0;
	total = 0;
	count = 0;
	while (j < 32)
	{
		total += b[j];
		if (total || j == 31)
		{
			char z = '0' + b[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
