/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strarr_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:49:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:07:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	free_strarr_all(char **arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen_arr((const char **)arr);
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
