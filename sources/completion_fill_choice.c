/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_fill_choice.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:57:20 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 09:46:49 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

static int	is_path(char *word)
{
	if (ft_strchr(word, '/'))
		return (true);
	return (false);
}

static void	complete_choice(char *word, t_list *(*finder)(char *))
{
	t_list	*new;
	t_list	*nxt;

	new = (*finder)(word);
	if (new)
	{
		while (new)
		{
			nxt = new->next;
			new->next = NULL;
			if (!ft_lstfind_head(&g_choice, new->content, new->content_size))
				ft_lstappend(&g_choice, new);
			else
			{
				if (new->content)
					free(new->content);
				new->content = NULL;
				free(new);
			}
			new = nxt;
		}
	}
}

int	fill_choice(char *line, char *word, int *insert_idx)
{
	int	dir;
	int	path;

	path = is_path(word);
	dir = is_directory(word, path, insert_idx);
	if (!path && is_first_word(line))
	{
		complete_choice(word, &ft_ifbin);
		complete_choice(word, &ft_ifbuiltin);
		complete_choice(word, &ft_ifalias);
	}
	return (dir);
}
