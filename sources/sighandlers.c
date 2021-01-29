/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:43:28 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/28 23:46:38 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "shell21.h"

void	ft_sighandler_winsize_change(int signum)
{
	(void)signum;
	ft_get_cursor_info();
}

void	ft_sighandler_ctrl_c(int signum)
{
	(void)signum;
	ft_putstr("^C\n");
	g_info.line[0] = '\0';
	env_set("?", "130", 0);
	g_info.exit = 1;
}

void	ft_sighandler_ctrl_z_return(int signum)
{
	ft_putnbr(signum);
	ft_putchar('\n');
	ft_putstr("\\_$> ");
	ft_get_cursor_info();
	ft_get_user_input(&g_info);
}

