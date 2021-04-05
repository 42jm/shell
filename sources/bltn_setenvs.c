/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_setenvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:16:38 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int	builtin_setenv(int argc, char **argv)
{
	if (argc > 3)
		return (ft_putusage(*argv, "name value"));
	if (argc == 1)
		return (env_put(1));
	if (ft_strchr(argv[1], '='))
		return (ft_putusage(*argv, "name value"));
	return (env_set(argv[1], argv[2], 1));
}

int	builtin_unsetenv(int argc, char **argv)
{
	if (argc < 2)
		return (put_error("Too few arguments", *argv));
	while (*(++argv))
		env_unset(*argv);
	return (0);
}

int	builtin_env(int argc, char **argv)
{
	char	**old_env;
	char	*varname;
	char	*valnew;
	int		ret;

	(void)argc;
	old_env = env_struct_to_strarr(g_envlst);
	while (*(++argv) && ft_strchr(*argv, '='))
	{
		varname = ft_strcdup(*argv, '=');
		valnew = ft_strchr(*argv, '=') + 1;
		env_set(varname, valnew, 1);
		free(varname);
	}
	ret = 0;
	if (*argv)
		ret = execute(argv);
	else
		env_put(1);
	env_free(g_envlst);
	g_envlst = env_strarr_to_struct(old_env);
	free_strarr_all(old_env);
	return (ret);
}
