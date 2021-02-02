/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

char	*astget_redirop(char *op)
{
	if (!op)
		return (NULL);
	while (ft_isdigit(*op))
		op++;
	if (!ft_strcmp(op, "<") || !ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
		return (op);
	if (!ft_strcmp(op, "<&") || !ft_strcmp(op, ">&") || !ft_strcmp(op, "<<"))
		return (op);
	return (NULL);
}

static int	handle_redir(t_astnode **at, int fd, char *op, char *word)
{
	if (!ft_strcmp(op, "<") || !ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
		return (astredir_simple(at, fd, op, word));
	else if (!ft_strcmp(op, "<&") || !ft_strcmp(op, ">&"))
		return (astredir_aggregate(at, fd, op, word));
	else if (!ft_strcmp(op, "<<"))
		return (astredir_heredoc(at, fd, op, word));
	return (put_error("invalid redirection operator", op));
}

int	astredir_handler(t_astnode **at, t_astnode *node)
{
	int		fd;
	char	*redir_op;
	char	*word;

	if (!node || !node->op)
		return (put_error("no arguments", "astredir_handler"));
	redir_op = astget_redirop(node->op);
	if (!redir_op)
		return (put_error("node is not a redir_op", node->op));
	if (!node->next || node->next->op)
		return (put_error("no word following redir_op", redir_op));
	word = node->next->content;
	fd = 0;
	if (ft_isdigit(*node->op))
		fd = ft_atoi(node->op);
	else if (*redir_op == '>')
		fd = 1;
	return (handle_redir(at, fd, redir_op, word));
}

int	astpop_redir(t_astnode **ahead, t_astnode **aredir)
{
	t_astnode	*node;
	t_astnode	*prev;

	*aredir = NULL;
	node = *ahead;
	prev = NULL;
	while (node && !astget_redirop(node->op))
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return (0);
	if (!node->next || node->next->op)
		return (put_error("no words directly after redir_op", node->op));
	if (prev)
		prev->next = node->next->next;
	else
		*ahead = node->next->next;
	node->next->next = NULL;
	*aredir = node;
	return (0);
}

int	astexec_redir(t_astnode **ahead)
{
	t_astnode	*node;
	int			ret;

	if (!ahead)
		return (put_error("no arguments", "astexec_redir"));
	node = NULL;
	ret = astpop_redir(ahead, &node);
	if (ret)
		return (ret);
	if (!node)
		return (astexec_assign(*ahead));
	ret = astredir_handler(ahead, node);
	free_node(node->next);
	free_node(node);
	return (ret);
}
