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

	binstr = ft_strdup("00000000");
	if (byte & 0x80)
		binstr[0] = '1';
	if (byte & 0x40)
		binstr[1] = '1';
	if (byte & 0x20)
		binstr[2] = '1';
	if (byte & 0x10)
		binstr[3] = '1';
	if (byte & 0x08)
		binstr[4] = '1';
	if (byte & 0x04)
		binstr[5] = '1';
	if (byte & 0x02)
		binstr[6] = '1';
	if (byte & 0x01)
		binstr[7] = '1';
	ft_putstr_fd(binstr, fd);
	free(binstr);
}
