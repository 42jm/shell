/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astredir_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	astredir_simple(t_astnode **at, int redir_fd, char *redir_op, char *path)
{
	int		word_fd;
	int		flags;
	mode_t	rights;

	if (!redir_op || !path)
		return (put_error("no arguments", "astredir_simple"));
	if (!ft_strcmp(redir_op, "<"))
		flags = O_RDONLY;
	if (!ft_strcmp(redir_op, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (!ft_strcmp(redir_op, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	word_fd = open(path, flags, rights);
	if (word_fd == -1)
		return (put_error("failed to open file", path));
	return (ast_localredir(at, word_fd, redir_fd));
}
