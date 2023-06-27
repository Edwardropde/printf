#include "main.h"
/**
 * get_precision - Determines precision for printing
 * @format: Formatted string where to print arguments
 * @j: List of arguments to be printed.
 * @arglist: list of arguments
 * Return: Precision
 */

int get_precision(const char *format, int *j, va_list arglist)
{

	int curr_j = *j + 1;
	int precision = -1;

	if (format[curr_j] != '.')
		return (precision);
	precision = 0;
	curr_j++;
	while (format[curr_j] != '\0')
	{
		if (is_digit(format[curr_j]))
		{
			precision *= 10;
			precision += format[curr_j] - '0';
			curr_j++;
		}
		else if (format[curr_j] == '*')
		{
			curr_j++;
			precision = va_arg(arglist, int);
			break;
		}
		else
		{
			break;
		}
	}
	*j = curr_j - 1;
	return (precision);
}

/**
 * get_width - Calculates width for printing
 * @format: Formatted string to print arguments.
 * @j: List of arguments to be printed.
 * @arglist: list of arguments.
 * Return: width.
 */

int get_width(const char *format, int *j, va_list arglist)
{

	int curr_j = *j + 1;
	int width = 0;

	while (format[curr_j] != '\0')
	{
		if (is_digit(format[curr_j]))
		{
			width *= 10;
			width += format[curr_j] - '0';
			curr_j++;
		}
		else if (format[curr_j] == '*')
		{
			curr_j++;
			width = va_arg(arglist, int);
			break;
		}
		else
		{
			break;
		}
	}
	*j = curr_j - 1;
	return (width);
}

/**
 * get_flags - Calculates active flags
 * @format: Formatted stringwhere to print arguments
 * @j: take a parameter.
 * Return: Flags:
 */

int get_flags(const char *format, int *j)
{

	int curr_j = *j + 1;
	int flags = 0;
	int k = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	while (format[curr_j] != '\0')
	{
		while (FLAGS_CH[k] != '\0')
		{
			if (format[curr_j] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}
			k++;
		}
		if (FLAGS_CH[k] == '\0')
			break;
		curr_j++;
	}
	*j = curr_j - 1;
	return (flags);
}

/**
 * get_size - Calculates the size to place on argument
 * @format: Formatted string to print argument
 * @j: List of argument to print
 * Return: Size
 */

int get_size(const char *format, int *j)
{

	int curr_j = *j + 1;
	int size = 0;

	while (format[curr_j] == 'l' || format[curr_j] == 'h')
	{
		if (format[curr_j] == 'l')
			size = S_LONG;
		else if (format[curr_j] == 'h')
			size = S_SHORT;
		curr_j++;
	}
	*j = curr_j - 1;
	return (size);
}
