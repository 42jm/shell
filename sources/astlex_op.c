/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astlex_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/28 22:22:26 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static char	*find_operator(char **oparr, char *ptr)
{
	char	*op;
	size_t	len_op;
	size_t	len_new;

	if (!oparr || !ptr)
		return (NULL);
	op = NULL;
	len_op = 0;
	while (*oparr)
	{
		len_new = ft_strlen(*oparr);
		if (!ft_strncmp(ptr, *oparr, len_new) && len_op < len_new)
		{
			op = *oparr;
			len_op = len_new;
		}
		oparr++;
	}
	return (op);
}

size_t		astlex_oplen(char *ptr)
{
	size_t		len_digits;
	size_t		len_op;
	static char	*oparr[16] =
	{
		"(", "<(", ">(", ")",
		";", "&",
		"&&", "||",
		"|",
		"<", ">", ">>", "<&", ">&", "<<",
		NULL
	};

	if (!ptr || !*ptr)
		return (0);
	len_digits = 0;
	while (ft_isdigit(ptr[len_digits]))
		len_digits++;
	ptr += len_digits;
	if (len_digits && *ptr != '>' && *ptr != '<')
		return (0);
	len_op = ft_strlen(find_operator(oparr, ptr));
	if (len_digits && !len_op)
		return (0);
	return (len_digits + len_op);
}
