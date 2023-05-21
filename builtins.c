/*
 * File: builtins.c
 * Auth: Falope Oluwaseun
 * 	 Darlington Ebom
 */

#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments.
 * Return: 1 if exit command encountered, 0 otherwise.
 */

int exit_shell(info_t *info)
{
	if (info->argv[1])
	{
		int exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (0);
		}
		info->err_num = exit_code;
	}
	else
		info->err_num = -1;

	return (1);
}

/**
 * change_directory - changes the current directory of the shell
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */

int change_directory(info_t *info)
{
	char *new_dir, buffer[1024];

	if (!info->argv[1])
		new_dir = _getenv(info, "HOME=");
	else if (_strcmp(info->argv[1], "-") == 0)
		new_dir = _getenv(info, "OLDPWD=");
	else
		new_dir = info->argv[1];

	if (!new_dir)
		new_dir = _getenv(info, "PWD=");

	if (chdir(new_dir) == -1)
	{
		print_error(info, "Unable to change directory to: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (1);
	}

	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));

	return (0);
}

/**
 * display_help - displays help information
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int display_help(info_t *info)
{
	_puts("Help information goes here.\n");
	return (0);
}

