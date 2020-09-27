/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:07:08 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:32:29 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	len = ft_strlen(needle);
	ptr = (char *)haystack;
	while (*ptr && i < n)
	{
		if (!ft_strncmp(ptr, needle, len))
		{
			if (len + i <= n)
				return (ptr);
			else
				return (NULL);
		}
		i++;
		ptr++;
	}
	return (NULL);
}
