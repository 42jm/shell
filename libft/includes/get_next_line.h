/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:28:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:13:54 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# define ERR_CHECK(X, Y) if(X) {free(Y); return (-1);}

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

int	get_next_line(const int fd, char **line);
#endif
