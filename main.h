#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 * @fmt: Format
 * @fn: The function
 */

struct fmt
{

	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 * @fmt: The format.
 * @fm_t: The function
 */

typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *j, va_list arglist, char buffer[],
		int flags, int width, int precision, int size);

/* Functions */

/* prints char, string, percent, int, binary functions */
int print_char(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_string(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_percent(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_int(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_binary(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);

/* print strings and char functions*/
int print_unsigned(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_octal(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_hexadecimal(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa_upper(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa(va_list arglist, char mapval[], char buffer[],
		int flags, char chflag, int width, int precision, int size);

/* print numbers */
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* print non printable characters */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* print memory address */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_non_printable(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_reverse(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);
int print_rot13string(va_list arglist, char buffer[],
		int flags, int width, int precision, int size);

/* Handle other specifiers */
int get_width(const char *format, int *j, va_list arglist);
int get_size(const char *format, int *j);
int get_flags(const char *format, int *j);
int get_precision(const char *format, int *j, va_list arglist);

/* print string in reverse */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* print string in rot 13 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* width handler */
int handle_write_char(char k, char buffer[],
		int flags, int width, int precision, int size);
int write_pointer(char buffer[], int ind, int lgth,
		int width, int flags, char dd, char otherch, int dd_start);
int write_number(int arglist, int ind, char buffer[],
		int flags, int width, int precision, int size);
int write_num(int ind, char buffer[],
		int flags, int width, int precision,
		int lgth, char dd, char otherch);
int write_unsgnd(int arglist, int ind,
char buffer[],
	int flags, int width, int precision, int size);

/**** UTILS ***/
int append_hexa_code(char ascii, char buffer[], int j);
int is_printable(char a);
long int convert_size_number(long int number, int size);
int is_digit(char a);
long int convert_size_unsgnd(unsigned long int number, int size);

#endif
