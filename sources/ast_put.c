/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	put_astlexed(t_astnode *token)
{
	if (!token)
		return ;
	while (token)
	{
		ft_putchar('(');
		if (!token->op)
			ft_putstr("NULL");
		else
			ft_putstr(token->op);
		ft_putstr(") ");
		ft_putstr(token->content);
		ft_putstr(";\n");
		token = token->next;
	}
}

static void	astput_word(t_astnode *token, size_t tabs)
{
	ft_putstr(" \"");
	ft_putstr(token->content);
	ft_putchar('"');
	put_astparsed(token->next, tabs);
}

void	put_astparsed(t_astnode *token, size_t tabs)
{
	size_t	i;

	if (!token)
		ft_putchar('\n');
	else if (!token->op)
		astput_word(token, tabs);
	else if (ft_strchr("><0123456789", *token->op))
	{
		ft_putchar(' ');
		ft_putstr(token->op);
		put_astparsed(token->next, tabs);
	}
	else
	{
		tabs++;
		ft_putstr(token->op);
		ft_putchar('\t');
		put_astparsed(token->content, tabs);
		if (!token->next)
			return ;
		i = 0;
		while (i++ < tabs)
			ft_putchar('\t');
		put_astparsed(token->next, tabs);
	}
}
