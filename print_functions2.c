#include "main.h"
/**
 * print_pointer - Prints value of a pointer variable
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array managing print
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	char otherch = 0, dd = ' ';
	unsigned long numberadrss;
	int ind = BUFF_SIZE - 2, lgth = 2, dd_start = 1;
	char mapval[] = "0123456789abcdef";
	void *adrss = va_arg(arglist, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrss == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	numberadrss = (unsigned long)adrss;
	for (; numberadrss > 0; numberadrss /= 16)
	{
		buffer[ind--] = mapval[numberadrss % 16];
		lgth++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		dd = '0';
	if (flags & F_PLUS)
		otherch = '+', lgth++;
	else if (flags & F_SPACE)
		otherch = ' ', lgth++;
	ind++;
	return (write_pointer(buffer, ind, lgth,
			width, flags, dd, otherch, dd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array managing print
 * @precision: Precision specification
 * @width: get width
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_non_printable(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	int set = 0;
	int j = 0;
	char *str = va_arg(arglist, char *);

	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));
	for (j = 0; str[j] != '\0'; j++)
	{
		if (is_printable(str[j]))
			buffer[j + set] = str[j];
		else
			set += append_hexa_code(str[j], buffer, j + set);
	}
	buffer[j + set] = '\0';
	return (write(1, buffer, j + set));
}

/**
 * print_reverse - Prints reverse string.
 * @arglist: List of arguments
 * @width: get width
 * @buffer: Buffer array managing print
 * @flags:  Calculates active flags
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	char *str;
	int j, cnt = 0;

	UNUSED(width);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(flags);

	str = va_arg(arglist, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}
	j = 0;
	while (str[j])
		j++;
	j--;
	while (j >= 0)
	{
		char z = str[j];

		write(1, &z, 1);
		cnt++;
		j--;
	}
	return (cnt);
}

/**
 * print_rot13string - Print string in rot13.
 * @arglist: List of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array managing print
 * @width: get width
 * @size: Size specifier
 * @precision: Precision specification
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list arglist, char buffer[],
		int flags, int width, int precision, int size)
{

	char y;
	char *str;
	unsigned int j, k;
	int cnt = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(arglist, char *);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);
	if (str == NULL)
		str = "(AHYY)";
	j = 0;
	while (str[j])
	{
		k = 0;
		while (in[k])
		{
			if (in[k] == str[j])
			{
				y = out[k];
				write(1, &y, 1);
				cnt++;
				break;
			}
			k++;
		}
		if (!in[k])
		{
			y = str[j];
			write(1, &y, 1);
			cnt++;
		}
		j++;
	}
	return (cnt);
}
