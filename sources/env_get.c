/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_list	*env_getentry(char *varname)
{
	t_list		*entry;
	t_envvar	*var;

	if (!g_envlst || !varname)
		return (NULL);
	var = NULL;
	entry = g_envlst;
	while (entry)
	{
		var = entry->content;
		if (!ft_strcmp(var->name, varname))
			break ;
		entry = entry->next;
	}
	return (entry);
}

t_envvar	*env_getvar(char *varname)
{
	t_list		*entry;

	entry = env_getentry(varname);
	if (!entry)
		return (NULL);
	return (entry->content);
}

char	*env_getvalue(char *varname)
{
	t_envvar	*var;

	var = env_getvar(varname);
	if (!var)
		return (NULL);
	return (var->value);
}
