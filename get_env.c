#include "shell.h"

/*
 * File: get_env.c
 * Auth: Falope Oluwaseun
 *      Darlington Ebom
 */

/**
 * get_environ-returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info);
int unset_env(info_t *info, char *var);
int set_env(info_t *info, char *var, char *value);

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_env_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env-Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var:the string env var property
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)

		return (0);

	while (node)
	{
		p = find_var_match(node->str, var);

		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;

			continue;
		}

		node = node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * set_env-initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var:the string env var property
 * @value:the string env var value
 * Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(strlen(var) + strlen(value) + 2);

	if (!buf)
		return (1);

	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, value);

	node = info->env;

	while (node)
	{
		p = find_var_match(node->str, var);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;

			return (0);
		}

		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1

		return (0);
}
