/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_userinput(int fd, char **abuf)
{
	ssize_t	ret;
	char	*buf;

	buf = ft_strnew(MAX_INPUT_LENGTH);
	*abuf = buf;
	ret = read(fd, buf, MAX_INPUT_LENGTH);
	if (ret < 0)
	{
		put_error("Failed read on input", NULL);
		free(buf);
		return (1);
	}
	if (ret >= MAX_INPUT_LENGTH)
	{
		put_error("Input too long", NULL);
		free(buf);
		return (2);
	}
	return (0);
}
