/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	builtin_cd(int argc, char **argv, t_list *envlst)
{
	char	*path;
	int		ret;

	if (argc > 2)
		return (put_error("Too many arguments", *argv));
	if (argc == 1)
		path = env_getvalue(envlst, "HOME");
	else if (!ft_strcmp(argv[1], "-"))
		path = env_getvalue(envlst, "OLDPWD");
	else
		path = argv[1];
	ret = chdir(path);
	if (ret)
		return (put_error("Chdir failed", *argv));
	path = getcwd(NULL, 0);
	env_set(envlst, "OLDPWD", env_getvalue(envlst, "PWD"));
	env_set(envlst, "PWD", path);
	if (argc > 1 && !ft_strcmp(argv[1], "-"))
		ft_putendl(path);
	free(path);
	return (0);
}