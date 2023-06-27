#include "main.h"
/**
 * get_flags - Calculates active flags
 * @format: Formatted string to print argumentsw
 * @l: take a parameter.
 * Return: Flags
 */

int get_flags(const char *format, int *l)
{

	int flags = 0;
	int k = 0, curr_l = *l;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	while (format[curr_l] != '\0')
	{
		k = 0;
		while (FLAGS_CH[k] != '\0')
		{
			if (format[curr_l] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}
			k++;
		}
		if (FLAGS_CH[k] == '\0')
		{
			break;
		}
		curr_l++;
	}
	*l = curr_l - 1;
	return (flags);
}
