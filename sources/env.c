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

#include "minishell.h"

t_list	*env_getentry(t_list *envlst, char *varname)
{
	char	*str;
	t_list	*entry;

	str = ft_strjoin(varname, "=");
	entry = ft_lstfind_head(&envlst, (void *)str, ft_strlen(str));
	free(str);
	return (entry);
}

char	*env_getvalue(t_list *envlst, char *varname)
{
	char	*ptr;
	t_list	*entry;

	entry = env_getentry(envlst, varname);
	if (!entry)
		return (NULL);
	ptr = ft_strchr((char *)(entry->content), '=') + 1;
	return (ptr);
}

int		env_set(t_list *envlst, char *varname, char *valnew)
{
	t_list	*entry;
	char	*tmp;
	char	*neo_str;
	t_list	*neo_entry;

	tmp = ft_strjoin(varname, "=");
	neo_str = ft_strjoin(tmp, valnew);
	free(tmp);
	entry = env_getentry(envlst, varname);
	if (entry)
	{
		free(entry->content);
		entry->content = (void *)neo_str;
		entry->content_size = ft_strlen(neo_str);
		return (0);
	}
	neo_entry = ft_lstnew((void *)neo_str, ft_strlen(neo_str));
	ft_lstappend(&envlst, neo_entry);
	return (0);
}

int		env_unset(t_list *envlst, char *varname)
{
	t_list	*entry;
	size_t	id;

	entry = env_getentry(envlst, varname);
	if (entry)
	{
		id = ft_lstget_id(&envlst, entry->content, entry->content_size);
		entry = ft_lstpop(&envlst, id);
		free(entry->content);
		free(entry);
	}
	return (0);
}

int		env_put(t_list *envlst)
{
	t_list	*entry;

	entry = envlst;
	while (entry)
	{
		ft_putendl((char *)(entry->content));
		entry = entry->next;
	}
	return (0);
}
