#include "main.h"
/**
 * is_printable - Evaluates if char can be printed
 * @a: Char to be evaluated.
 * Return: 1 if a is printable, 0 otherwise
 */

int is_printable(char a)
{

	int printable = 0;
	int j = 32;

	while (j < 127)
	{
		if (a == 1)
		{
			printable = 1;
			break;
		}
		j++;
	}
	return (printable);
}

/**
 * append_hexa_code - Append ASCII in hexadecimal code to buffer
 * @j: Index at which to start appending.
 * @buffer: Array of chars.
 * @ascii: ASCII code.
 * Return: Always 3
 */

int append_hexa_code(char ascii, char buffer[], int j)
{

	char mapval[] = "0123456789ABCDEF";
	int index = 0;

	if (ascii < 0)
		ascii *= -1;
	for (index = 0; index < 3; index++)
	{
		if (index == 0)
			buffer[j++] = '\\';
		else if (index == 1)
			buffer[j++] = 'x';
		else
		{
			buffer[j++] = mapval[ascii / 16];
			buffer[j] = mapval[ascii % 16];
		}
	}
	return (3);
}

/**
 * is_digit - Checks if char is a digit
 * @a: Char to be checked
 * Return: 1 if a is a digit, 0 otherwise
 */

int is_digit(char a)
{

	int digit = 0;

	while (digit <= 9)
	{
		if (a == digit + '0')
			return (1);
		digit++;
	}
	return (0);
}

/**
 * convert_size_number - Casts number to specified size
 * @number: Number to be casted.
 * @size: Number showing type to be casted.
 * Return: Casted value of number
 */

long int convert_size_number(long int number, int size)
{

	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);
	return ((int)number);
}

/**
 * convert_size_unsgnd - Casts number to specified size
 * @number: Number to cast
 * @size: Number showing type to be casted
 * Return: Casted value of number
 */

long int convert_size_unsgnd(unsigned long int number, int size)
{

	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);
	return ((unsigned int)number);
}
