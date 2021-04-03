/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:59:06 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/03 17:56:02 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

int 	ft_alias_type(char *name)
{
	char	*val;

	val = ft_get_alias(name);
	if (val)
	{
		ft_putstr(name);
		ft_putstr(" is aliased to `");
		ft_putstr(val);
		ft_putstr("'\n");
		return (1);
	}
	else
		return (0);
}

int 	ft_file_type(char *name)
{
	char	*val;

	val = ft_get_path(name);
	if (val)
	{
		ft_putstr(name);
		ft_putstr(" is ");
		ft_putstr(val);
		ft_putstr("\n");
		free(val);
		return (1);
	}
	else
		return (0);
}

int 	ft_isbltn(char *name)
{
	int			i;
	static char	*bltn_names[] = {
		"alias", "unalias", "pwd", \
		"echo", "exit", "cd", \
		"set", "unset", "export", \
		"setenv", "unsetenv", "env", \
		"jobs", "fg", "bg", NULL};
	i = -1;
	while (bltn_names[++i])
		if (!ft_strcmp(bltn_names[i], name))
			return (1);
	return (0);
}

int 	builtin_type(int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (ft_alias_type(argv[i]))
			;
		else if (ft_isbltn(argv[i]))
		{
			ft_putstr(argv[i]);
			ft_putstr(" is a shell builtin\n");
		}
		else if (ft_file_type(argv[i]))
			;
		else
		{
			ft_putstr("type: ");
			ft_putstr(argv[i]);
			ft_putstr(": not found\n");
		}
	}
	return (0);
}
