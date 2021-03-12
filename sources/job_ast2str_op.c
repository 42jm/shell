/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_ast2str_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

int	astcmdstr_op_after(t_astnode *node, char **acmd)
{
	if (node->content)
	{
		astcmdstr(node->content, acmd);
		if (ft_strcmp(node->op, ";"))
			astcmdstr_cpy(acmd, " ");
	}
	astcmdstr_cpy(acmd, node->op);
	if (!node->next)
		return (0);
	astcmdstr_cpy(acmd, " ");
	return (astcmdstr(node->next, acmd));
}

int	astcmdstr_op_before(t_astnode *node, char **acmd)
{
	astcmdstr_cpy(acmd, node->op);
	if (!node->content)
		return (0);
	astcmdstr_cpy(acmd, " ");
	return (astcmdstr(node->content, acmd));
}

int	astcmdstr_op_around(t_astnode *node, char **acmd)
{
	char	*left;
	char	*right;

	oparound_get_braces(node->op, &left, &right);
	if (!right || !left)
	{
		if (left)
			free(left);
		if (right)
			free(right);
		return (put_error("malloc failed", "astcmdstr_op_around"));
	}
	astcmdstr_cpy(acmd, left);
	astcmdstr(node->content, acmd);
	astcmdstr_cpy(acmd, right);
	free(left);
	free(right);
	if (!node->next)
		return (0);
	astcmdstr_cpy(acmd, " ");
	return (astcmdstr(node->next, acmd));
}

int	astcmdstr_op_ignore(t_astnode *node, char **acmd)
{
	astcmdstr(node->content, acmd);
	if (!node->next)
		return (0);
	astcmdstr_cpy(acmd, " ");
	return (astcmdstr(node->next, acmd));
}

int	astcmdstr_op_heredoc(t_astnode *node, char **acmd)
{
	char	*word_delim;

	if (node->content)
		astcmdstr(node->content, acmd);
	astcmdstr_cpy(acmd, "<< ");
	if (!node->next || node->next->op || !node->next->content)
		return (put_error("no delimiter word set", "astcmdstr_op_heredoc"));
	word_delim = node->next->content;
	astcmdstr(node->next, acmd);
	astcmdstr_cpy(acmd, "\n");
	while (*g_lines && ft_strcmp(*g_lines, word_delim))
	{
		astcmdstr_cpy(acmd, *g_lines);
		astcmdstr_cpy(acmd, "\n");
		g_lines++;
	}
	if (*g_lines && !ft_strcmp(*g_lines, word_delim))
		g_lines++;
	astcmdstr_cpy(acmd, word_delim);
	astcmdstr_cpy(acmd, "\n");
	return (0);
}
