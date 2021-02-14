/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size2_char_typing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:49:37 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/13 19:49:49 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_size2_char(char *line, char *chr)
{
	if (chr[0] == '~' || chr[0] == '^' || chr[0] == '`')
	{
		line = ft_insert_char(line, chr[0]);
		line = ft_insert_char(line, chr[1]);
	}
	return (line);
}
