/*
 * File: interact.c
 * Auth: Falope Oluwaseun
 *       Darlington Ebom
 */

#include "shell.h"

/**
 * is_interactive - checks if shell is running in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int is_interactive(info_t *info)
{
	int is_tty = isatty(STDIN_FILENO);
	int is_valid_fd = info->readfd <= 2;

	return (is_tty && is_valid_fd);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if true , 0 otherwise
 */

int is_delimiter(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_alpha - checks for an alphabetic character
 * @c: the character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_integer - converts a string to an integer
 * @s: String to be converted
 *
 * Return: the converted integer, or 0 if no numbers in the string
 */

int string_to_integer(char *s)
{
	int sign = 1;
	int flag = 0;
	unsigned int result = 0;
	int output;

	for (; *s != '\0' && flag != 2; s++)
	{
		if (*s == '-')
			sign *= -1;

		if (*s >= '0' && *s <= '9')
		{
			flag = 1;
			result *= 10;
			result += (*s - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	output = (sign == -1) ? -result : result;
	return (output);
}
