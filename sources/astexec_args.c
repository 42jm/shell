/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "jobs_42sh.h"

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
	args = ast_to_strarr(head);
	if (!args)
		return (put_error("malloc failed", "astexec_args"));
	ret = execute(args);
	free_strarr_all(args);
	if (ret)
		env_lastret_set(ret);
	return (ret);
}
