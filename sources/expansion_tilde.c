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

#include "header_42sh.h"

static char	*get_tilde_path(char *str, size_t *alen)
{
	*alen = 1;
	if (!ft_strcmp(str, "~") || !ft_strncmp(str, "~/", 2))
		return (env_getvalue("HOME"));
	*alen = 2;
	if (!ft_strcmp(str, "~+") || !ft_strncmp(str, "~+/", 3))
		return (env_getvalue("PWD"));
	if (!ft_strcmp(str, "~-") || !ft_strncmp(str, "~-/", 3))
		return (env_getvalue("OLDPWD"));
	*alen = 0;
	return (NULL);
}

int	expand_tilde(t_astnode *node)
{
	char	*path;
	char	*tmp;
	size_t	len;

	if (!node || !node->content)
		return (put_error("no arguments", "expand_tilde"));
	path = get_tilde_path(node->content, &len);
	if (!path)
		return (0);
	tmp = node->content;
	if (!ft_strcmp(node->content, "~") || \
!ft_strcmp(node->content, "~+") || \
!ft_strcmp(node->content, "~-"))
		node->content = ft_strdup(path);
	else
		node->content = ft_strjoin(path, (char *)node->content + len);
	if (!node->content)
	{
		node->content = tmp;
		return (put_error("malloc failed", "expand_tilde"));
	}
	free(tmp);
	return (0);
}
