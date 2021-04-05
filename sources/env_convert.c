/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/04/05 22:46:57 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

t_list	*env_strarr_to_struct(char **envp)
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

char	**env_struct_to_strarr(t_list *entry)
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

int	env_init(int argc, char **argv, char **envp)
{
	int	ret;

	g_envlst = env_strarr_to_struct(envp);
	ret = 1;
	if (g_envlst)
		ret = 0;
	if (!ret)
		ret = env_set("?", "0", 0);
	if (!ret)
	{
		if (argc == 1)
			ret = builtin_set(0, argv);
		else
			ret = builtin_set(argc, argv);
	}
	if (ret > 0)
		return (-ret - 1);
	return (ret);
}
