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

#include "shell21.h"

int	astexec_andor(t_astnode **at)
{
	t_astnode	*node;
	int			ret;
	char		*lastret;
	int			is_lastret;

	node = *at;
	ret = 0;
	lastret = env_getvalue("?");
	if (!lastret)
		return (put_error("envir_var '?' is not set", "astexec_andor"));
	is_lastret = ft_strcmp(lastret, "0");
	if (!ft_strcmp(node->op, "&&") && !is_lastret)
		ret = ast_execute((t_astnode **)&node->content);
	else if (!ft_strcmp(node->op, "||") && is_lastret)
		ret = ast_execute((t_astnode **)&node->content);
	if (ret < 0)
		return (ret);
	return (ast_execute((t_astnode **)&node->next));
}

int	astexec_amper(t_astnode **at)
{
	pid_t		pid;
	t_astnode	*node;
	int			ret;

	node = *at;
	pid = fork();
	if (pid == -1)
		return (put_error("failed fork", node->op));
	if (!pid)
	{
		ast_execute((t_astnode **)&node->content);
		exit(0);
	}
	ret = env_set("?", "0", 0);
	if (ret)
		return (ret);
	return (ast_execute((t_astnode **)&node->next));
}

int	astexec_semicol(t_astnode **at)
{
	t_astnode	*node;
	int			ret;

	node = *at;
	ret = ast_execute((t_astnode **)&node->content);
	if (ret < 0)
		return (ret);
	return (ast_execute((t_astnode **)&node->next));
}
