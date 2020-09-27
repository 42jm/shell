/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_binary_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:54:53 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 12:55:22 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_binary_fd(char byte, int fd)
{
	char	*binstr;

	binstr = (char *)malloc(sizeof(char) * 8);
	binstr[0] = byte & 0x80 ? '1' : '0';
	binstr[1] = byte & 0x40 ? '1' : '0';
	binstr[2] = byte & 0x20 ? '1' : '0';
	binstr[3] = byte & 0x10 ? '1' : '0';
	binstr[4] = byte & 0x08 ? '1' : '0';
	binstr[5] = byte & 0x04 ? '1' : '0';
	binstr[6] = byte & 0x02 ? '1' : '0';
	binstr[7] = byte & 0x01 ? '1' : '0';
	ft_putstr_fd(binstr, fd);
	free(binstr);
}
