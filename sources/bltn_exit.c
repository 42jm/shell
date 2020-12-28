/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 14:00:40 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	builtin_exit(int argc, char **argv)
{
	int	ret;

	pr_putstr_fd("exit\n", 2);
	if (argc > 2)
		put_error("Too many arguments", *argv);
	ret = -1;
	if (argc == 2)
	{
		if (ft_isdigit((int)argv[1][0]))
			ret = -1 * (ft_atoi(argv[1]) + 1);
		else
			ret = put_error_ret("Numeric argument required", argv[1], 2);
	}
	return (ret);
}
