/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:42:41 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 12:13:29 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(char *s, size_t len)
{
	char	*newstr;
	size_t	i;

	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		return (ft_strdup(s));
	newstr = (char *)malloc((len + 1) * sizeof(*s));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[len] = '\0';
	return (newstr);
}
