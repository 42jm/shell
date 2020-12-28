/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_simplecmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	astexec_args(t_astnode *head)
{
	t_astnode	*node;
	char		**args;
	int			ret;

	if (!head)
		return (put_error("no arguments", "astexec_args"));
	if (head->op && !ft_strcmp(head->op, "{}"))
		return (astexec_curly(&head));
	if (head->op && !ft_strcmp(head->op, "()"))
		return (astexec_paren(&head));
	node = head;
	while (node && !node->op)
		node = node->next;
	if (node)
		return (put_error("ast operator found as argument", "astexec_args"));
	if (!(args = ast_to_strarr(head)))
		return (put_error("malloc failed", "astexec_args"));
	ret = execute(args);
	free_strarr_all(args);
	return (ret);
}

int	astexec_simplecmd(t_astnode **at)
{
	int			ret;
	t_astnode	*node;

	node = *at;
	while (node)
	{
		if (node->op && \
		(!ft_strcmp(node->op, "<()") || !ft_strcmp(node->op, ">()")))
			return (expand_op(at, node));
		node = node->next;
	}
	if ((ret = expand_word(*at)))
		return (ret);
	return (astexec_redir(at));
}
