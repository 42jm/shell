/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_braces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int	astexec_curly(t_astnode **at)
{
	t_astnode	*head;
	t_astnode	*node;
	static char	*authorized_ops[4] = {";", "()", "{}", NULL };

	head = *at;
	node = head->content;
	if (head->next)
		return (put_error("a token is following the braces", "{}"));
	if (!node)
		return (put_error("nothing inside braces", "{}"));
	if (node->op && !ft_arrstr(authorized_ops, node->op))
		return (put_error("unauthorized op inside braces", node->op));
	return (ast_execute(&node));
}

int	astexec_paren(t_astnode **at)
{
	t_astnode	*head;
	t_astnode	*node;
	pid_t		pid;
	int			wstatus;
	int			ret;

	head = *at;
	node = head->content;
	if (head->next)
		return (put_error("a token is following the parentheses", head->op));
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", head->op));
	if (!pid)
		ast_execute(&node);
	if (!pid)
		exit(0);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		ret = env_lastret_set(WEXITSTATUS(wstatus));
		if (ret)
			return (ret);
	}
	return (ast_execute(&head->next));
}
