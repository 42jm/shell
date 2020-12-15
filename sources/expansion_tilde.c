/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	expand_tilde(t_astnode *node)
{
	char	*home_path;
	char	*tmp;

	if (!node || !node->content)
		return (put_error("no arguments", "expand_tilde"));
	if (ft_strcmp(node->content, "~") && ft_strncmp(node->content, "~/", 2))
		return (0);
	home_path = env_getvalue("HOME");
	if (!home_path)
		return (put_error("cannot find value of $HOME", "expand_tilde"));
	tmp = node->content;
	if (ft_strlen(node->content) == 1)
		node->content = ft_strdup(home_path);
	else
		node->content = ft_strjoin(home_path, (char *)node->content + 1);
	if (!node->content)
	{
		node->content = tmp;
		return (put_error("malloc failed", "expand_tilde"));
	}
	free(tmp);
	return (0);
}
