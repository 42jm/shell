/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	pipe_dupexe(t_astnode **at, t_list *envlst, int *fildes, int io)
{
	int	ret;

	if (io != 0 && io != 1)
		return (put_error("argument io is neither 1 nor 0", "pipe_dupexe"));
	if (close(fildes[1 - io]) == -1)
		return (put_error("failed to close unused pipe fd", "pipe_dupexe"));
	ret = ast_localredir(at, envlst, fildes[io], io);
	if (close(fildes[io]) == -1)
		return (put_error("failed to close used pipe fd", "pipe_dupexe"));
	return (ret);
}

int	astexec_pipe(t_astnode **at, t_list *envlst)
{
	int			fildes[2];
	pid_t		pid;
	t_astnode	*node;

	if (!at || !*at)
		return (put_error("no arguments", "astexec_pipe"));
	node = *at;
	if (!node->content || !node->next)
		return (put_error("a pipe needs two commands", node->op));
	if (pipe(fildes) == -1)
		return (put_error("failed to create pipe", node->op));
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
	{
		signal(SIGINT, sighandle_ignore);
		pipe_dupexe((t_astnode **)&node->content, envlst, fildes, 1);
		return (-1);
	}
	return (pipe_dupexe((t_astnode **)&node->next, envlst, fildes, 0));
}