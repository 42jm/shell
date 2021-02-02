/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astredir_local.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	ast_localclose(t_astnode **at, int fd)
{
	int	tmp;
	int	ret;

	tmp = dup(fd);
	if (tmp == -1)
		return (put_error("failed to store fd", "localclose"));
	if (close(fd) == -1)
		return (put_error("failed to close fd", "localclose"));
	ret = ast_execute(at);
	if (dup2(tmp, fd) == -1)
		return (put_error("failed to restore fd", "localclose"));
	if (close(tmp) == -1)
		return (put_error("failed to close tmp fd", "localclose"));
	return (ret);
}

int	ast_localredir(t_astnode **at, int dst, int src)
{
	int	tmp_src;
	int	ret;

	tmp_src = dup(src);
	if (tmp_src == -1)
		return (put_error("failed to store source fd", "localredir"));
	if (dup2(dst, src) == -1)
		return (put_error("failed to replace source fd", "localredir"));
	ret = ast_execute(at);
	if (dup2(tmp_src, src) == -1)
		return (put_error("failed to restore source fd", "localredir"));
	if (close(tmp_src) == -1)
		return (put_error("failed to close tmp fd", "localredir"));
	return (ret);
}
