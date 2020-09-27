/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:56:50 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/11 14:42:54 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_randr(int min, int max)
{
	unsigned int	uint;
	double			range;
	int				fd;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &uint, sizeof(unsigned int));
	close(fd);
	range = (double)uint / (double)UINT_MAX;
	range *= (double)DELTA(min, max - 1);
	return (min + (int)(range + 0.5));
}

/*
#include <stdio.h>
#include <stdlib.h>
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("usage: %s range_min range_max\n", argv[0]);
		return (1);
	}
	printf("%d\n", ft_randr(atoi(argv[1]), atoi(argv[2])));
	return (0);
}
*/
