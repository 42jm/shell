/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astparse_andor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static int	andor_list(t_astnode *token)
{
	t_astnode	*ptr;
	t_astnode	*prev;
	int			ret;

	if (!token)
		return (0);
	ptr = token->next;
	if (!ptr)
		return (put_error("syntax error near token", token->op));
	prev = token;
	while (ptr)
	{
		if (ptr->op && (!ft_strcmp(ptr->op, "&&") || !ft_strcmp(ptr->op, "||")))
			break ;
		prev = ptr;
		ptr = ptr->next;
	}
	prev->next = NULL;
	ret = ast_parser(&token->next);
	if (ret)
		return (ret);
	token->content = token->next;
	token->next = ptr;
	return (andor_list(ptr));
}

int	handle_andor(t_astnode **atoken, t_astnode *prev, t_astnode *head)
{
	t_astnode	*ptr;

	if (!prev)
		return (put_error("syntax error near token", head->op));
	ptr = token_new(";");
	if (!ptr)
		return (1);
	prev->next = NULL;
	if (ast_parser(&head))
	{
		free(ptr);
		return (1);
	}
	ptr->content = head;
	ptr->next = *atoken;
	*atoken = ptr;
	return (andor_list(ptr->next));
}
