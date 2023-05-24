/*
 * File: print_env.c
 * Auth: Falope Oluwaseun
 *       Darlington Ebom
 */

#include "shell.h"

int print_env(info_t *info);
char *find_env_variable(info_t *info, const char *name);
int set_env_variable(info_t *info);
int unset_env_variable(info_t *info);
int populate_env_list(info_t *info);

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int print_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * find_env_variable - finds the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: Environment variable name
 * Return: The value of the environment variable, or NULL if not found
 */

char *find_env_variable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = strstr(node->str, name);
		if (p && p == node->str && p[strlen(name)] == '=')
			return (p + strlen(name) + 1);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_variable - sets the value of an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int set_env_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (setenv(info->argv[1], info->argv[2], 1) == 0)
		return (0);

	return (1);
}

/**
 * unset_env_variable - removes an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int unset_env_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
		unsetenv(info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates the environment variable linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	char **env_ptr = environ;

	while (*env_ptr)
	{
		add_node_end(&node, *env_ptr, 0);
		env_ptr++;
	}

	info->env = node;
	return (0);
}
