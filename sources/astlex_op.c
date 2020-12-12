/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astlex_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

size_t	astlex_oplen(char *ptr)
{
	size_t	len_digits;
	size_t	len_op;

	if (!ptr || !*ptr)
		return (0);
	len_digits = 0;
	while (ft_isdigit(ptr[len_digits]))
		len_digits++;
	ptr += len_digits;
	if (len_digits && *ptr != '>' && *ptr != '<')
		return (0);
	len_op = ft_strlen(find_operator(g_oparr, ptr));
	if (len_digits && !len_op)
		return (0);
	return (len_digits + len_op);
}
