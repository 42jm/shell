/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:25:15 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 12:56:32 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_arr(char **arr, size_t n, char sep)
{
	size_t	len;
	char	*join;
	char	*ptr;
	size_t	i;

	i = 0;
	len = 0;
	if (sep)
		len = n - 1;
	while (i < n)
		len += ft_strlen(arr[i++]);
	join = ft_strnew(len);
	if (!join)
		return (NULL);
	i = 0;
	ptr = join;
	while (i < n)
	{
		len = ft_strlen(arr[i]);
		ft_memcpy(ptr, arr[i], len);
		ptr += len;
		if (++i < n && sep)
			*ptr++ = sep;
	}
	return (join);
}
