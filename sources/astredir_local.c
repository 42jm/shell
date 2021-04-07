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

#include "header_42sh.h"
#include "jobs_42sh.h"

int	ast_localclose(t_astnode **at, int fd)
{
	int	tmp;
	int	ret;
	int	termsaved;

	tmp = dup(fd);
	if (tmp == -1)
		return (put_error("failed to store fd", "localclose"));
	termsaved = 0;
	if (!fd && !g_shell->terminal)
	{
		termsaved = 1;
		g_shell->terminal = tmp;
	}
	if (close(fd) == -1)
		return (put_error("failed to close fd", "localclose"));
	ret = ast_execute(at);
	if (dup2(tmp, fd) == -1)
		return (put_error("failed to restore fd", "localclose"));
	if (termsaved)
		g_shell->terminal = fd;
	if (close(tmp) == -1)
		return (put_error("failed to close tmp fd", "localclose"));
	return (ret);
}

int	ast_localredir(t_astnode **at, int dst, int src)
{
	int	tmp_src;
	int	ret;
	int	termsaved;

	tmp_src = dup(src);
	if (tmp_src == -1)
		return (put_error("failed to store source fd", "localredir"));
	termsaved = 0;
	if (!src && !g_shell->terminal)
	{
		termsaved = 1;
		g_shell->terminal = tmp_src;
	}
	if (dup2(dst, src) == -1)
		return (put_error("failed to replace source fd", "localredir"));
	ret = ast_execute(at);
	if (dup2(tmp_src, src) == -1)
		return (put_error("failed to restore source fd", "localredir"));
	if (termsaved)
		g_shell->terminal = src;
	if (close(tmp_src) == -1)
		return (put_error("failed to close tmp fd", "localredir"));
	return (ret);
}
