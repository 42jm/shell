/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_envvar	*envvar_new(char *name, char *value, bool exportable)
{
	t_envvar	*var;

	var = (t_envvar *)malloc(sizeof(*var));
	if (!var)
		return (NULL);
	var->exportable = exportable;
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	var->value = NULL;
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
		{
			free(var->name);
			free(var);
			return (NULL);
		}
	}
	return (var);
}

t_list	*env_new(char *name, char *value, bool exportable)
{
	t_envvar	*var;
	t_list		*entry;

	var = envvar_new(name, value, exportable);
	if (!var)
		return (NULL);
	entry = (t_list *)malloc(sizeof(*entry));
	if (!entry)
	{
		free(var->name);
		if (var->value)
			free(var->value);
		free(var);
		return (NULL);
	}
	entry->content = var;
	entry->content_size = sizeof(*var);
	entry->next = NULL;
	return (entry);
}

t_list	*env_splitnew(char *str, bool exportable)
{
	char	*ptr;
	char	*name;
	char	*value;
	t_list	*entry;

	if (!str)
		return (NULL);
	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (NULL);
	value = ptr + 1;
	name = ft_strdup(str);
	if (!name)
		return (NULL);
	ptr = ft_strchr(name, '=');
	*ptr = '\0';
	entry = env_new(name, value, exportable);
	free(name);
	return (entry);
}
