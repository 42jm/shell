/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astlex_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_astnode	*token_new(char *ptr)
{
	t_astnode	*token;

	token = (t_astnode *)malloc(sizeof(t_astnode));
	if (!token)
	{
		put_error("malloc failed to create struct", "token_new");
		return (NULL);
	}
	token->op = NULL;
	if (ptr)
	{
		token->op = ft_strndup(ptr, astlex_oplen(ptr));
		if (!token->op)
		{
			put_error("malloc failed to create op str", "token_new");
			return (NULL);
		}
	}
	token->content = NULL;
	token->next = NULL;
	return (token);
}

int			token_delimit(t_astnode *token, char *input, size_t len)
{
	if (!token->op && !(token->content = (void *)ft_strndup(input, len)))
		return (put_error_ret("malloc failed", "token_delimit", 1));
	return (ast_lexer(input + len, &token->next));
}
