/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:43:28 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/23 19:06:16 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "shell21.h"

void	ft_sighandler_winsize_change(int signum)
{
	(void)signum;
	ft_get_cursor_info();
}

void	ft_sighandler_ignore(int signum)
{
	(void)signum;
}

void	ft_sighandler_ctrl_c(int signum)
{
	(void)signum;
	ft_putstr("^C\n");
	write(g_info.fd[1], "\0", 1);
	g_info.line[0] = '\0';
	env_set("?", "130", 0);
	g_info.exit = 1;
}

void	ft_sighandler_ctrl_z_return(int signum)
{
	(void)signum;
	ft_putchar('\n');
	g_info.line[0] = '\0';
	g_info.exit = 1;
	ft_get_cursor_info();
}

void	ft_ignore_allsig(void)
{
	signal(SIGWINCH, ft_sighandler_ignore);
	signal(SIGINT, ft_sighandler_ignore);
	signal(SIGCONT, ft_sighandler_ignore);
}
