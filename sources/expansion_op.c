/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	replace_node_by_fdstr(t_astnode *node, int fd)
{
	char	*fd_str;

	fd_str = ft_itoa(fd);
	if (!fd_str)
		return (put_error("malloc failed", "substitute_process"));
	free(node->op);
	node->op = NULL;
	free_ast(node->content);
	node->content = ft_strjoin("/dev/fd/", fd_str);
	free(fd_str);
	if (!node->content)
		return (put_error("malloc failed", "substitute_process"));
	return (0);
}

static int	process_substitute(t_astnode *node, int *fildes, int fd_child)
{
	int	ret;
	int	tmp;

	if ((tmp = dup(fd_child)) == -1)
		return (put_error("failed to backup fd", node->op));
	if ((dup2(fildes[fd_child], fd_child)) == -1)
		return (put_error("failed to set new fd", node->op));
	ret = ast_execute(&node);
	if ((dup2(tmp, fd_child)) == -1)
		ret = put_error("failed to reset fd to backup", node->op);
	if (close(tmp) == -1)
		ret = put_error("failed to close fd backup", node->op);
	return (ret);
}

int			expand_op(t_astnode **at, t_astnode *node)
{
	int		ret;
	int		fildes[2];
	int		fd_child;
	int		fd_paren;
	pid_t	pid;

	if (pipe(fildes) == -1 || (pid = fork()) == -1)
		return (put_error("pipe/fork failed", "substitute_process"));
	fd_child = *node->op == '<' ? 1 : 0;
	fd_paren = 1 - fd_child;
	if (!pid)
	{
		close(fildes[fd_paren]);
		ret = process_substitute(node->content, fildes, fd_child);
		close(fildes[fd_child]);
		return (ret < 0 ? ret : -ret - 1);
	}
	close(fildes[fd_child]);
	if ((ret = replace_node_by_fdstr(node, fildes[fd_paren])))
		return (ret);
	ret = astexec_simplecmd(at);
	close(fildes[fd_paren]);
	return (ret);
}
