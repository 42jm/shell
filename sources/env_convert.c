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

#include "shell21.h"

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
		if (var->exportable)
			envp[i++] = ft_strcjoin('=', var->name, var->value);
		entry = entry->next;
	}
	while (i <= len)
		envp[i++] = NULL;
	return (envp);
}

int			env_init(int argc, char **argv, char **envp)
{
	int		ret;

	g_envlst = env_strarr_to_struct(envp);
	ret = g_envlst ? 0 : 1;
	if (!ret)
		ret = env_set("?", "0", 0);
	if (!ret)
		ret = builtin_set(argc == 1 ? 0 : argc, argv);
	return (ret > 0 ? -ret - 1 : ret);
}
