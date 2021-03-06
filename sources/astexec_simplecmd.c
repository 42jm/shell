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

#include "header_42sh.h"
#include "jobs_42sh.h"

static int	expand_words_then_redir(t_astnode **at)
{
	int	ret;

	ret = expand_words(at);
	if (!ret)
		ret = astexec_redir(at);
	return (ret);
}

static int	simplecmd_complete_job(int ret)
{
	if (!ret)
		return (job_complete_blueprint());
	job_free(&g_shell->job_blueprint);
	return (ret);
}

static t_astnode	*simplecmd_get_op(t_astnode *node, char *op)
{
	while (node)
	{
		if (!op && !node->op)
			return (node);
		if (op && node->op && !ft_strcmp(op, node->op))
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	astexec_simplecmd(t_astnode **at)
{
	int			ret;
	t_astnode	*node;
	int			job_spawned;
	static char	*expandable_ops[] = {">()", "<()", NULL};

	node = *at;
	job_spawned = 0;
	if (g_shell->is_interactive && !g_shell->job_blueprint && \
!simplecmd_get_op(node, "{}"))
	{
		ret = job_start_new(*at);
		if (ret)
			return (ret);
		job_spawned = 1;
	}
	node = *at;
	while (node && (!node->op || !ft_arrstr(expandable_ops, node->op)))
		node = node->next;
	if (node)
		ret = expand_op(at, node);
	else
		ret = expand_words_then_redir(at);
	if (!job_spawned)
		return (ret);
	return (simplecmd_complete_job(ret));
}
