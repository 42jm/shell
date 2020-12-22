/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	ast_execute(t_astnode **at)
{
	t_astnode	*node;

	if (!at || !*at)
		return (0);
	node = *at;
	if (!node->op)
		return (astexec_simplecmd(at));
	else if (!ft_strcmp(node->op, ";"))
		return (astexec_semicol(at));
	else if (!ft_strcmp(node->op, "&"))
		return (astexec_amper(at));
	else if (!ft_strcmp(node->op, "|"))
		return (astexec_pipe(at));
	else if (!ft_strcmp(node->op, "&&") || !ft_strcmp(node->op, "||"))
		return (astexec_andor(at));
	else if (!ft_strcmp(node->op, "()"))
		return (astexec_paren(at));
	return (astexec_simplecmd(at));
}
