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

int	builtin_setenv(int argc, char **argv)
{
	if (argc > 3)
		return (put_error("Too many arguments", *argv));
	if (argc > 1)
		return (env_set(argv[1], argv[2], 1));
	env_put(0);
	return (0);
}

int	builtin_unsetenv(int argc, char **argv)
{
	if (argc < 2)
		return (put_error("Not enough arguments", *argv));
	while (*(++argv))
		env_unset(*argv);
	return (0);
}
