/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:48:15 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/31 18:04:21 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

void	ft_putalias(t_alias *alias)
{
	ft_putstr("alias ");
	ft_putstr(alias->name);
	ft_putchar('=');
	ft_putstr(alias->link);
	ft_putchar('\n');
}

void	ft_print_alias(char *alias)
{
	t_alias	*i;

	i = g_alias;
	while (i)
	{
		if (!alias)
		{
			ft_putalias(i);
		}
		else if (!ft_strcmp(alias, i->name))
		{
			ft_putalias(i);
			return ;
		}
		i = i->next;
	}
	if (alias)
	{
		pr_putstr_fd("42sh: alias: ", 2);
		pr_putstr_fd(alias, 2);
		pr_putstr_fd(": not found\n", 2);
	}
}

void	ft_add_alias(t_alias *new)
{
	t_alias	*i;

	if (!g_alias || ft_strcmp(new->name, g_alias->name) <= 0)
	{
		new->next = g_alias;
		g_alias = new;
	}
	else
	{
		i = g_alias;
		while (i->next)
		{
			if (ft_strcmp(new->name, i->next->name) <= 0)
			{
				new->next = i->next;
				i->next = new;
				return ;
			}
			i = i->next;
		}
		new->next = i->next;
		i->next = new;
	}
}

int 	ft_new_alias(char *s)
{
	int		i;
	t_alias	*new;

	new = (t_alias *)ft_memalloc(sizeof(t_alias));
	if (!new)
		return (-1);
	i = 0;
	while (s[i] != '=')
		i++;
	new->name = ft_strndup(s, i);
	if (!(new->name))
		return (-1);
	new->link = ft_strdup(&s[i + 1]);
	if (!(new->link))
		return (-1);
	ft_add_alias(new);
	return (0);
}

int 	builtin_alias(int argc, char **argv)
{
	int	i;

	if (!ft_get_options(argv, ""))
		return (1);
	if (!ft_count_args(argc, argv))
		ft_print_alias(NULL);
	else
	{
		i = 0;
		while (argv[++i])
		{
			if (!ft_strchr(argv[i], '='))
				ft_print_alias(argv[i]);
			else if (ft_new_alias(argv[i]) == -1)
				return (1);
		}
	}
	return (0);
}
