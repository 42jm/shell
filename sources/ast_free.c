/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	free_node(t_astnode *node)
{
	if (!node)
		return ;
	if (node->content)
	{
		if (!node->op)
			free(node->content);
		else if (!ft_strcmp(node->op, ";") || !ft_strcmp(node->op, "&") \
		|| !ft_strcmp(node->op, "&&") \
		|| !ft_strcmp(node->op, "||") \
		|| !ft_strcmp(node->op, "|") \
		|| !ft_strcmp(node->op, "{") \
		|| !ft_strcmp(node->op, "}") \
		|| !ft_strcmp(node->op, "{}") \
		|| !ft_strcmp(node->op, "(") \
		|| !ft_strcmp(node->op, ")") \
		|| !ft_strcmp(node->op, "()") \
		|| !ft_strcmp(node->op, "<()") \
		|| !ft_strcmp(node->op, ">()"))
			free_ast(node->content);
		else
			put_error(node->op, "cannot free contents of unkown op node");
	}
	if (node->op)
		free(node->op);
	free(node);
}

void	free_ast(t_astnode *node)
{
	if (node->next)
		free_ast(node->next);
	free_node(node);
}
