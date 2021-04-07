/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astparse_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static char	*get_heredoc(char *word)
{
	char	*heredoc;
	char	*tmp;

	heredoc = NULL;
	while (*g_lines && ft_strcmp(*g_lines, word))
	{
		if (heredoc)
		{
			tmp = heredoc;
			heredoc = ft_strcjoin('\n', heredoc, *g_lines);
			free(tmp);
		}
		else
			heredoc = ft_strdup(*g_lines);
		g_lines++;
	}
	if (*g_lines && !ft_strcmp(*g_lines, word))
		g_lines++;
	else
		put_error("heredoc delimitor word not found (warning)", word);
	return (heredoc);
}

static int	fillup_heredoc(t_astnode *token)
{
	char	*word;
	char	*heredoc;

	word = NULL;
	if (token->next && !token->next->op && token->next->content)
		word = token->next->content;
	if (!word)
		return (put_error("heredoc delimitor word not set", "handle_heredoc"));
	heredoc = get_heredoc(word);
	if (heredoc)
	{
		token->content = ft_strjoin(heredoc, "\n");
		free(heredoc);
	}
	else
		token->content = ft_strdup("");
	return (0);
}

int	ast_fillup_heredocs(t_astnode *lexed)
{
	int	ret;

	ret = 0;
	while (lexed)
	{
		if (lexed->op && !ft_strcmp(lexed->op, "<<"))
			ret = fillup_heredoc(lexed);
		if (ret)
			return (ret);
		lexed = lexed->next;
	}
	return (0);
}
