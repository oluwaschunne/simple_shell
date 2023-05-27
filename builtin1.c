/*
 * File: builtin1.c
 * Auth: Falope Oluwaseun
 *       Darlington Ebom
 */

#include "shell.h"

/**
 * history_command - displays the history list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int history_command(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: Structure containing potential arguments.
 * @alias: The alias string to remove.
 * Return: always 0 on success, 1 on error.
 */

int unset_alias(info_t *info, char *alias)
{
	char *equal_ptr, equal_char;
	int ret;

	equal_ptr = _strchr(alias, '=');
	if (!equal_ptr)
		return (1);

	equal_char = *equal_ptr;
	*equal_ptr = '\0';

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));

	*equal_ptr = equal_char;
	return (ret);
}

/**
 * set_alias - sets an alias in the alias list
 * @info: Structure containing potential arguments.
 * @alias: The alias string to set.
 * Return: 0 on success, 1 on error.
 */

int set_alias(info_t *info, char *alias)
{
	char *equal_ptr;

	equal_ptr = _strchr(alias, '=');
	if (!equal_ptr)
		return (1);

	if (!(*++equal_ptr))
		return (unset_alias(info, alias));

	unset_alias(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias - prints the value of an alias
 * @alias_node: The alias node to print.
 * Return: Always 0 on success, 1 on error.
 */

int print_alias(list_t *alias_node)
{
	char *equal_ptr = NULL, *alias_value = NULL;

	if (alias_node)
	{
		equal_ptr = _strchr(alias_node->str, '=');
		for (alias_value = alias_node->str; alias_value <= equal_ptr; alias_value++)
			_putchar(*alias_value);
		_putchar('\'');
		_puts(equal_ptr + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * alias_command - implements the behavior of the alias command
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */

int alias_command(info_t *info)
{
	int i;
	char *equal_ptr = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_ptr = _strchr(info->argv[i], '=');
		if (equal_ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
