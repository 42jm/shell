/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(int argc, char **argv)
{
	int	i;

	pr_putstr_fd("exit\n", 2);
	if (argc > 2)
		put_error("Too many arguments", *argv);
	i = 0;
	if (argc == 2)
	{
		if (ft_isdigit((int)argv[1][0]))
			i = ft_atoi(argv[1]);
		else
			put_error("Numeric argument required", argv[1]);
	}
	exit(i);
}
