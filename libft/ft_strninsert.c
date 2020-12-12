/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strninstert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:40:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/24 16:04:22 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strninsert(char *str, char *needle, size_t n)
{
	char	*ret;
	size_t	len_str;
	size_t	len_needle;

	if (!str || !needle)
		return (NULL);
	len_needle = ft_strlen(needle);
	len_str = ft_strlen(str);
	if (n > len_str)
		return (NULL);
	ret = ft_strnew(len_str + len_needle + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, str, n);
	ft_strcpy(ret + n, needle);
	ft_strcpy(ret + n + len_needle, str + n);
	return (ret);
}
