/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unalias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 19:21:23 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/30 19:24:43 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

void	ft_free_alias(void)
{
	t_alias	*i;

	if (g_alias)
	{
		while (g_alias)
		{
			i = g_alias;
			g_alias = g_alias->next;
			free(i->name);
			free(i->link);
			free(i);
		}
	}
}

int 	ft_rm_alias(char *alias)
{
	t_alias	*i;
	t_alias	*prev;

	i = g_alias;
	prev = NULL;
	while (i)
	{
		if (!ft_strcmp(alias, i->name))
		{
			if (!prev)
				g_alias = i->next;
			else
				prev->next = i->next;
			free(i->name);
			free(i->link);
			free(i);
			return (1);
		}
		prev = i;
		i = i->next;
	}
	ft_putstr("42sh: unalias: ");
	ft_putstr(alias);
	ft_putstr(": not found\n");
	return (0);
}

int 	builtin_unalias(int argc, char **argv)
{
	int		i;
	char	*opt;

	opt = ft_get_options(argv, "a");
	if (!opt)
		return (ft_error("unalias: usage: unalias [-a] name [name ...]\n", 1));
	if (opt[0] == 'a')
	{
		ft_free_alias();
		free(opt);
		return (0);
	}
	if (!ft_count_args(argc, argv))
		ft_putstr("unalias: usage: unalias [-a] name [name ...]\n");
	else
	{
		i = 1;
		while (argv[i] && argv[i][0] == '-' && argv[i][1])
			i++;
		while (argv[i])
			ft_rm_alias(argv[i++]);
	}
	return (0);
}
