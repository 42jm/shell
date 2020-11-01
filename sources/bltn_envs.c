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

#include "21sh.h"

int	builtin_setenv(int argc, char **argv, t_list *envlst)
{
	if (argc > 3)
		return (put_error("Too many arguments", *argv));
	if (argc > 1)
		return (env_set(envlst, argv[1], argv[2]));
	env_put(envlst);
	return (0);
}

int	builtin_unsetenv(int argc, char **argv, t_list *envlst)
{
	if (argc < 2)
		return (put_error("Too few arguments", *argv));
	while (*(++argv))
		env_unset(envlst, *argv);
	return (0);
}

int	builtin_env(int argc, char **argv, t_list *envlst)
{
	t_list	*neo_env;
	char	*varname;
	char	*valnew;
	int		ret;

	(void)argc;
	neo_env = ft_lstdup(envlst);
	while (*(++argv) && ft_strchr(*argv, '='))
	{
		varname = ft_strcdup(*argv, '=');
		valnew = ft_strchr(*argv, '=') + 1;
		env_set(neo_env, varname, valnew);
		free(varname);
	}
	ret = 0;
	if (*argv)
		ret = execute_any(argv, neo_env);
	else
		env_put(neo_env);
	ft_lstfree(neo_env);
	return (ret);
}
