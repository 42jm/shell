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

#include "21sh.h"

int			read_userinput(int fd, char ***ainput)
{
	ssize_t	len;
	size_t	ret;
	char	*buf;

	buf = ft_strnew(MAX_INPUT_LENGTH);
	len = read(fd, buf, MAX_INPUT_LENGTH);
	ret = 0;
	if (len < 0 && (ret = 1))
		put_error("Failed read on input", NULL);
	else if (len >= MAX_INPUT_LENGTH && (ret = 2))
		put_error("Input too long", NULL);
	if (ret)
		return (ret);
	if (!*buf)
	{
		free(buf);
		if (!(buf = ft_strdup("exit")))
			return (put_error("failed to strdup 'exit'", NULL));
	}
	*ainput = ft_strcsplit_all(buf, '\n');
	if (!*ainput && (ret = 3))
		put_error("strsplit failed", "read_userinput");
	free(buf);
	return (ret);
}
