/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_list		*env_strarr_to_struct(char **envp)
{
	t_list		*head;
	t_list		*entry;

	if (!envp)
		return (NULL);
	head = NULL;
	while (*envp)
	{
		if (!head)
		{
			head = env_splitnew(*envp, 1);
			entry = head;
			if (!head)
				put_error("bad format, envir var omitted", *envp);
			envp++;
			continue ;
		}
		entry->next = env_splitnew(*envp, 1);
		if (entry->next)
			entry = entry->next;
		else
			put_error("bad format, envir var omitted", *envp);
		envp++;
	}
	return (head);
}

char		**env_struct_to_strarr(t_list *entry)
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
		envp[i] = ft_strcjoin('=', var->name, var->value);
		i++;
		entry = entry->next;
	}
	envp[len] = NULL;
	return (envp);
}
