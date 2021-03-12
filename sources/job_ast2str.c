/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_ast2str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs_42sh.h"

int	astcmdstr_cpy(char **acmd, char *str)
{
	ft_strcpy(*acmd, str);
	*acmd += ft_strlen(str);
	return (0);
}

int	astcmdstr_op(t_astnode *node, char **acmd)
{
	static char	*op_around[] = {"{}", "()", "<()", ">()", NULL};
	static char	*op_before[] = {"&&", "||", NULL};
	static char	*op_ignore[] = {"&|", NULL};

	if (ft_arrstr(op_around, node->op))
		return (astcmdstr_op_around(node, acmd));
	if (ft_arrstr(op_before, node->op))
		return (astcmdstr_op_before(node, acmd));
	if (ft_arrstr(op_ignore, node->op))
		return (astcmdstr_op_ignore(node, acmd));
	if (!ft_strcmp(node->op, "<<"))
		return (astcmdstr_op_heredoc(node, acmd));
	return (astcmdstr_op_after(node, acmd));
}

int	astcmdstr(t_astnode *node, char **acmd)
{
	if (!node)
		return (0);
	if (node->op)
		return (astcmdstr_op(node, acmd));
	if (!node->content)
		return (0);
	astcmdstr_cpy(acmd, node->content);
	if (!node->next)
		return (0);
	astcmdstr_cpy(acmd, " ");
	return (astcmdstr(node->next, acmd));
}

char	*job_ast2str(t_astnode *head)
{
	char	*cmdstr;
	char	*ptr;
	char	**lines;

	cmdstr = ft_strnew(MAX_INPUT_LENGTH * 3);
	if (!cmdstr)
	{
		put_error("initial malloc failed", "ast_to_cmdstr");
		return (NULL);
	}
	ptr = cmdstr;
	lines = g_lines;
	if (astcmdstr(head, &ptr))
	{
		free(cmdstr);
		return (NULL);
	}
	g_lines = lines;
	ptr = cmdstr;
	cmdstr = ft_strdup(ptr);
	if (!cmdstr)
		put_error("final malloc failed", "ast_to_cmdstr");
	free(ptr);
	return (cmdstr);
}
