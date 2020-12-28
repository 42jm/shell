/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:16:38 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	unset_greaternbrs(int i)
{
	char	*nbr;
	int		ret;

	nbr = ft_itoa(i);
	if (!nbr)
		return (put_error("malloc failed", "unset_greaternbrs"));
	while (env_getentry(nbr))
	{
		ret = env_unset(nbr);
		free(nbr);
		if (ret)
			return (ret);
		nbr = ft_itoa(++i);
		if (!nbr)
			return (put_error("malloc failed", "unset_greaternbrs"));
	}
	if (nbr)
		free(nbr);
	return (0);
}

int			builtin_set(int argc, char **argv)
{
	int		i;
	char	*nbr;
	int		ret;

	if (!g_envlst)
		return (put_error("envir does not exist", "builtin_set"));
	if (argc == 1)
		return (env_put(0));
	i = 0;
	while (i < (argc = argc ? argc : 1))
	{
		if (!(nbr = ft_itoa(i)))
			return (put_error("malloc failed", "envset_nbr"));
		ret = env_set(nbr, argv[i++], 0);
		free(nbr);
		if (ret)
			return (ret);
	}
	if (!(nbr = ft_itoa(argc - 1)))
		return (put_error("malloc failed", "builtin_set"));
	ret = env_set("#", nbr, 0);
	free(nbr);
	if (ret)
		return (ret);
	return (unset_greaternbrs(i));
}

int			builtin_unset(int argc, char **argv)
{
	if (argc < 2)
		return (put_error("Not enough arguments", *argv));
	while (*(++argv))
		env_unset(*argv);
	return (0);
}

static int	env_export(char *str)
{
	t_list		*entry;
	t_envvar	*var_new;
	t_envvar	*var_old;
	int			ret;

	if (ft_strchr(str, '='))
		entry = env_splitnew(str, 1);
	else
		entry = env_new(str, NULL, 1);
	if (!entry)
		return (put_error("malloc failed", "env_export"));
	var_new = entry->content;
	var_old = env_getvar(var_new->name);
	if (var_old)
	{
		if (!ft_strchr(str, '=') && var_old->value)
			if (!(var_new->value = ft_strdup(var_old->value)))
				return (put_error("malloc failed", "env_export"));
		if ((ret = env_unset(var_old->name)))
			return (ret);
	}
	ft_lstappend(&g_envlst, entry);
	return (0);
}

int			builtin_export(int argc, char **argv)
{
	int	ret;

	(void)argc;
	argv++;
	while (*argv && !ft_strcmp(*argv, "-p"))
		argv++;
	if (!*argv)
		return (envput_export());
	while (*argv)
	{
		if (ft_strchr("#?0123456789", **argv) || !bashvar_len(*argv))
			return (put_error("not a valid variable name", *argv));
		ret = env_export(*argv);
		if (ret)
			return (ret);
		argv++;
	}
	return (0);
}
