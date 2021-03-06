/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:17:09 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/06 22:19:44 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\b' || c == '\r')
		return (true);
	return (false);
}
