/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astredir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static int	heredoc_write(int *fildes, t_astnode *node)
{
	int	ret;

	ret = 0;
	if (close(fildes[0]) == -1)
		ret = put_error("child failed to close pipe (read)", "heredoc");
	ft_putstr_fd(node->content, fildes[1]);
	if (close(fildes[1]) == -1)
		ret = put_error("child failed to close pipe (write)", "heredoc");
	return (ret);
}

int	astredir_heredoc(t_astnode **at, int fd, char *redir_op, t_astnode *node)
{
	int		fildes[2];
	pid_t	pid;
	int		ret;

	if (!g_lines)
		return (put_error("no arguments", "astredir_heredoc"));
	if (pipe(fildes) == -1)
		return (put_error("pipe failed", redir_op));
	pid = fork();
	if (!pid)
	{
		heredoc_write(fildes, node);
		exit(0);
	}
	if (close(fildes[1]) == -1)
		return (put_error("parent failed to close pipe write side", "heredoc"));
	ret = ast_localredir(at, fildes[0], fd);
	if (close(fildes[0]) == -1)
		return (put_error("parent failed to close pipe read side", "heredoc"));
	return (ret);
}
