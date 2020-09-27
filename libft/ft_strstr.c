/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:07:08 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:19:48 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;
	char	*ptr;

	if (*needle == '\0')
		return ((char *)haystack);
	len = ft_strlen(haystack);
	ptr = ft_strnstr(haystack, needle, len);
	return (ptr);
}
