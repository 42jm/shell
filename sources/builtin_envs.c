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
	while (++argv)
		env_unset(envlst, *argv);
	return (0);
}
