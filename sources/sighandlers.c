/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:43:28 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/05 23:15:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"
#include "jobs_42sh.h"

void	ft_sighandler_winsize_change(int signum)
{
	(void)signum;
	ft_get_cursor_info();
}

/*
** NOTE: called when using ^C in the prompt
*/

void	ft_sighandler_ctrl_c(int signum)
{
	(void)signum;
	ft_putendl("^C");
	g_info.line[0] = '\0';
	env_set("?", "130", 0);
	g_info.exit = 1;
	close(g_info.fd[0]);
}

void	ft_sighandler_ctrl_z_return(int signum)
{
	(void)signum;
	g_info.line[0] = '\0';
	g_info.exit = 1;
	g_info.sigcont = 1;
}
