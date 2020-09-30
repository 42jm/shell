/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_envs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_setenv(int argc, char **argv, t_list *envlst)
{
	t_list	*entry;

	if (argc > 3)
		return (put_error("too many arguments", *argv));
	if (argc > 1)
		return (env_set(envlst, argv[1], argv[2]));
	env_put(envlst);
	return (0);
}

int	builtin_unsetenv(int argc, char **argv, t_list *envlst)
{
	t_list	*entry;

	if (argc < 2)
		return (put_error("too few arguments", *argv));
	while (*(++argv))
		env_unset(envlst, *argv);
	return (0);
}

int	builtin_env(int argc, char **argv, t_list *envlst)
{
	t_list	*neo_env;
	char	*varname;
	char	*valnew;

	//ft_putendl("balise0");
	neo_env = ft_lstdup(envlst);
	//ft_putendl("balise1");
	while (*(++argv) && ft_strchr(*argv, '='))
	{
		//ft_putendl("balise2");
		varname = ft_strcdup(*argv, '=');
		valnew = ft_strchr(*argv, '=') + 1;
		env_set(neo_env, varname, valnew);
		free(varname);
	}
	//ft_putendl("balise3");
	if (*argv)
	{
		//ft_putendl("balise4");
		execute_any(argv, neo_env);
	}
	else
	{
		//ft_putendl("balise5");
		env_put(neo_env);
	}
	//ft_putendl("balise6");
	ft_lstfree(neo_env);
	//ft_putendl("balise7");
	return (0);
}
