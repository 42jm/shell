/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_separ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	astexec_andor(t_astnode **at)
{
	t_astnode	*node;
	int			ret;

	node = *at;
	ret = 0;
	if (!ft_strcmp(node->op, "&&") && !g_childret)
		ret = ast_execute((t_astnode **)&node->content);
	else if (!ft_strcmp(node->op, "||") && g_childret)
		ret = ast_execute((t_astnode **)&node->content);
	if (ret == -1)
		return (-1);
	return (ast_execute((t_astnode **)&node->next));
}

int	astexec_amper(t_astnode **at)
{
	pid_t		pid;
	t_astnode	*node;

	node = *at;
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
	{
		ast_execute((t_astnode **)&node->content);
		return (-1);
	}
	g_childret = 0;
	return (ast_execute((t_astnode **)&node->next));
}

int	astexec_semicol(t_astnode **at)
{
	t_astnode	*node;

	node = *at;
	if (ast_execute((t_astnode **)&node->content) == -1)
		return (-1);
	return (ast_execute((t_astnode **)&node->next));
}
