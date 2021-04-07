/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_get_shell_variable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:49:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 11:49:37 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	**get_shell_variable(t_list *entry)
{
	size_t		len;
	size_t		i;
	t_envvar	*var;
	char		**envp;

	if (!entry)
		return (NULL);
	len = ft_lstlen(&entry);
	if (!len)
		return (NULL);
	envp = (char **)malloc(sizeof(*envp) * (len + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < len && entry)
	{
		var = entry->content;
		envp[i++] = ft_strcjoin('=', var->name, var->value);
		entry = entry->next;
	}
	while (i <= len)
		envp[i++] = NULL;
	return (envp);
}
