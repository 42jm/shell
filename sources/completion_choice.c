/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_choice.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:20:51 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 08:41:00 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

t_list	*make_choice(const void *content)
{
	t_list	*new;

	if (content)
	{
		new = ft_lstnew(content, sizeof(char) + ft_strlen(content));
		if (!new)
			return (NULL);
		if (!g_choice)
			return (new);
		ft_lstadd(&g_choice, new);
	}
	return (g_choice);
}

int	get_longest_choice_len(void)
{
	t_list	*curr;
	size_t	len_max;

	curr = g_choice;
	len_max = 0;
	while (curr && curr->content_size)
	{
		if (!len_max || ft_strlen(curr->content) > len_max)
			len_max = ft_strlen(curr->content);
		curr = curr->next;
	}
	return (len_max);
}

void	free_choice(void)
{
	t_list	*curr;
	t_list	*nxt;

	curr = g_choice;
	while (curr)
	{
		nxt = curr->next;
		if (curr->content)
			free(curr->content);
		curr->content = NULL;
		free(curr);
		curr = nxt;
	}
	g_choice = NULL;
}
