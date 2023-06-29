#include "main.h"
/**
 * handle_write_char - Prints  string
 * @k: char types
 * @buffer: Buffer array manage print
 * @flags:  Calculates active flags
 * @width: gets width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int handle_write_char(char k, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = 0;
	char dd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		dd = '0';
	buffer[j++] = k;
	buffer[j] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		j = 0;
		while (j < width - 1)
		{
			buffer[BUFF_SIZE - j - 2] = dd;
			j++;
		}
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
				write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints string
 * @arglist: List of arguments
 * @ind: char types.
 * @buffer: Buffer array to manage print
 * @flags:  Finds active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int write_number(int arglist, int ind, char buffer[],
	int flags, int width, int precision, int size)
{

	int lgth = BUFF_SIZE - ind - 1;
	char dd = ' ', otherch = 0;
	int chars_printed = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		dd = '0';
	if (arglist)
		otherch = '-';
	else if (flags & F_PLUS)
		otherch = '+';
	else if (flags & F_SPACE)
		otherch = ' ';
	while (chars_printed < lgth)
	{
		if (buffer[ind] == '\0')
			break;
		chars_printed += write_num(ind, buffer, flags, width,
				precision, lgth, dd, otherch);
	}
	return (chars_printed);
}

/**
 * write_num - Use buffer to write number
 * @ind: First index on buffer
 * @width: width
 * @buffer: Buffer
 * @flags: Flags
 * @lgth: Number length
 * @otherch: Extra char
 * @dd: Padding char
 * @prec: Precision specifier
 * Return: Number of printed chars.
 */

int write_num(int ind, char buffer[],
	int flags, int width, int precision,
	int lgth, char dd, char otherch)
{

	int j, dd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = dd = ' ';
	if (prec > 0 && prec < lgth)
		dd = ' ';
	while (prec > lgth)
		buffer[--ind] = '0', lgth++;
	if (otherch != 0)
		lgth++;
	if (width > lgth)
	{
		for (j = 1; j < width - lgth + 1; j++)
			buffer[j] = dd;
		buffer[j] = '\0';
		if (flags & F_MINUS && dd == ' ')
		{
			if (otherch)
				buffer[--ind] = otherch;
			return (write(1, &buffer[ind], lgth) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && dd == ' ')
		{
			if (otherch)
				buffer[--ind] = otherch;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[ind], lgth));
		}
		else if (!(flags & F_MINUS) && dd == '0')
		{
			if (otherch)
				buffer[--dd_start] = otherch;
			return (write(1, &buffer[dd_start], j - dd_start) +
					write(1, &buffer[ind], lgth - (1 - dd_start)));
		}
	}
	if (otherch)
		buffer[--ind] = otherch;
	return (write(1, &buffer[ind], lgth));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @arglist: Number indicating if the num is negative
 * @buffer: Array of chars
 * @precision: Precision specifier
 * @ind: Index at which the number starts in the buffer
 * @flags: Flags specifiers
 * @size: Size specifier
 * @width: Width specifier
 * Return: Number of written chars.
 */

int write_unsgnd(int arglist, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{

	int lgth = BUFF_SIZE - ind - 1, j = 0;
	char dd = ' ';

	UNUSED(arglist);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < lgth)
		dd = ' ';
	while (precision > lgth)
	{
		buffer[--ind] = '0';
		lgth++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		dd = '0';
	if (width > lgth)
	{
		for (j = 0; j < width - lgth; j++)
			buffer[j] = dd;
		buffer[j] = '\0';
		if (flags & F_MINUS)
			return (write(1, &buffer[ind], lgth) + write(1, &buffer[0], j));
		else
			return (write(1, &buffer[0], j) + write(1, &buffer[ind], lgth));
	}
	return (write(1, &buffer[ind], lgth));
}

/**
 * write_pointer - Print memory address
 * @buffer: Arrays of chars
 * @ind: Index where number begins in the buffer
 * @flags: Flags
 * @prec: Precision
 * @lgth: Number length
 * @dd_start: Index at where padding should begin
 * @dd: Char indicating padding
 * @width: Width
 * @otherch: Char indicating additional char
 * Return: Number of written chars.
 */

int write_pointer(char buffer[], int ind, int lgth,
	int width, int flags, char dd, char otherch, int dd_start)
{

	int j;

	if (width > lgth)
	{
		for (j = 3; j < width - lgth + 3; j++)
			buffer[j] = dd;
		buffer[j] = '\0';
		if ((flags & F_MINUS && dd == ' ') || (!(flags & F_MINUS) && dd == ' '))
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (otherch)
				buffer[--ind] = otherch;
			if (flags & F_MINUS)
				return (write(1, &buffer[ind], lgth) + write(1, &buffer[3], j - 3));
			else
				return (write(1, &buffer[3], j - 3) + write(1, &buffer[ind], lgth));
		}
		else if (!(flags & F_MINUS) && dd == '0')
		{
			if (otherch)
				buffer[--dd_start] = otherch;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[dd_start], j - dd_start) +
				write(1, &buffer[ind], lgth - (1 - dd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (otherch)
		buffer[--ind] = otherch;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
