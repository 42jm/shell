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

int astexec_andor(t_astnode **at, t_list *envlst)
{
	t_astnode	*node;

	node = *at;
	if (!ft_strcmp(node->op, "&&") && !g_childret)
		g_childret = ast_execute((t_astnode **)&node->content, envlst);
	else if (!ft_strcmp(node->op, "||") && g_childret)
		g_childret = ast_execute((t_astnode **)&node->content, envlst);
	return (ast_execute((t_astnode **)&node->next, envlst));
}

int	astexec_amper(t_astnode **at, t_list *envlst)
{
	pid_t		pid;
	t_astnode	*node;

	node = *at;
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
	{
		ast_execute((t_astnode **)&node->content, envlst);
		return (-1);
	}
	g_childret = 0;
	//TODO	append pid to global link list of all bg jobs
	//TODO	fix `cat &' does not auto exit
	return (ast_execute((t_astnode **)&node->next, envlst));
}

int	astexec_semicol(t_astnode **at, t_list *envlst)
{
	t_astnode	*node;

	node = *at;
	g_childret = ast_execute((t_astnode **)&node->content, envlst);
	return (ast_execute((t_astnode **)&node->next, envlst));
}
