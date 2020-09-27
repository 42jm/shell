/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:20:25 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 12:53:54 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pr_putstr_fd(char const *s, int fd)
{
	size_t	len;

	if (!s)
		return (1);
	if (pr_strlen(s, &len) < 0)
		return (2);
	if (write(fd, s, len) == -1)
		return (3);
	return (0);
}
