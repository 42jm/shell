/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:08:55 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/08 15:11:04 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char delim)
{
	char	*head;
	char	*buf;
	char	*tmp;

	head = ft_strnew(0);
	buf = ft_strnew(PAGEBUF);
	while (read(fd, buf, PAGEBUF) && !ft_strchr(buf, delim))
	{
		tmp = ft_strjoin(head, buf);
		free(head);
		head = tmp;
		ft_bzero(buf, PAGEBUF);
	}
	if (ft_strchr(buf, delim))
	{
		tmp = ft_strcdup(buf, delim);
		free(buf);
		buf = tmp;
		tmp = ft_strjoin(head, buf);
		free(head);
		head = tmp;
	}
	free(buf);
	return (head);
}
