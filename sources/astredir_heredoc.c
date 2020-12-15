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

#include "21sh.h"

static int	heredoc_write(int *fildes, char *word)
{
	signal(SIGINT, sighandle_ignore);
	if (close(fildes[0]) == -1)
		return (put_error("child failed to close pipe (read)", "heredoc"));
	while (*g_lines)
	{
		if (!ft_strcmp(*g_lines, word))
			break ;
		ft_putendl_fd(*g_lines, fildes[1]);
		g_lines++;
	}
	if (*g_lines && !ft_strcmp(*g_lines, word))
		g_lines++;
	else
		return (put_error("delimitor word not found", word));
	if (close(fildes[1]) == -1)
		return (put_error("child failed to close pipe (write)", "heredoc"));
	return (-1);
}

int			astredir_heredoc(t_astnode **at, int fd, char *redir_op, char *word)
{
	int		fildes[2];
	pid_t	pid;
	int		ret;

	if (!g_lines || !*g_lines)
		return (put_error("no arguments", "astredir_heredoc"));
	if (pipe(fildes) == -1)
		return (put_error("pipe failed", redir_op));
	pid = fork();
	if (!pid)
		return (heredoc_write(fildes, word));
	if (close(fildes[1]) == -1)
		return (put_error("parent failed to close pipe write side", "heredoc"));
	ret = ast_localredir(at, fildes[0], fd);
	if (close(fildes[0]) == -1)
		return (put_error("parent failed to close pipe read side", "heredoc"));
	while (*g_lines && ft_strcmp(*g_lines, word))
		g_lines++;
	if (*g_lines && !ft_strcmp(*g_lines, word))
		g_lines++;
	return (ret);
}
