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

#include "21sh.h"

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

char	*env_getvalue(char *varname)
{
	t_list		*entry;
	t_envvar	*var;

	entry = env_getentry(varname);
	if (!entry)
		return (NULL);
	var = entry->content;
	return (var->value);
}
