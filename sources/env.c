/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int	env_lastret_set(int lastret)
{
	char	*str;
	int		ret;

	str = ft_itoa(lastret);
	if (!str)
		return (put_error("malloc failed", "envset_lastret"));
	ret = env_set("?", str, 0);
	free(str);
	return (ret);
}

static int	env_update(t_envvar *var, char *val, int exportable)
{
	if (exportable >= 0)
		var->exportable = exportable;
	if (var->value)
		free(var->value);
	var->value = ft_strdup(val);
	return (0);
}

int	env_set(char *varname, char *valnew, int exportable)
{
	t_list		*entry;
	t_envvar	*var;

	entry = env_getentry(varname);
	if (entry)
		return (env_update(entry->content, valnew, exportable));
	entry = (t_list *)malloc(sizeof(*entry));
	var = (t_envvar *)malloc(sizeof(*var));
	if (!entry || !var)
		return (put_error("malloc failed", "env_set"));
	if (exportable < -1 || 0 < exportable)
		var->exportable = 1;
	else
		var->exportable = 0;
	var->name = ft_strdup(varname);
	var->value = ft_strdup(valnew);
	entry->content = var;
	entry->content_size = sizeof(*var);
	entry->next = NULL;
	ft_lstappend(&g_envlst, entry);
	return (0);
}

int	env_unset(char *varname)
{
	t_list		*entry;
	t_envvar	*var;
	size_t		len;

	entry = env_getentry(varname);
	if (!entry)
		return (0);
	len = ft_lstlen_upto(g_envlst, entry);
	if (!len)
		return (put_error("failed to find id of entry in envir", "env_unset"));
	entry = ft_lstpop(&g_envlst, len - 1);
	if (!entry)
		return (put_error("failed to pop entry from envir", "env_unset"));
	var = entry->content;
	free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	free(entry);
	return (0);
}

void	env_free(t_list *entry)
{
	t_envvar	*var;
	t_list		*next;

	if (!entry)
		return ;
	var = entry->content;
	next = entry->next;
	free(entry);
	free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	env_free(next);
}
