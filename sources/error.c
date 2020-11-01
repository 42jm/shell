/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	put_error_ret(char *message, char *arg, int ret)
{
	pr_putstr_fd("21sh: ", 2);
	if (arg)
	{
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": ", 2);
	}
	pr_putstr_fd(message, 2);
	pr_putstr_fd("\n", 2);
	return (ret);
}

int	put_error(char *message, char *arg)
{
	return (put_error_ret(message, arg, 1));
}
