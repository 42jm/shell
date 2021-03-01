/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 20:08:53 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	opt_append(char *options, char chr)
{
	while (*options)
	{
		if (*options == chr)
			ft_strcpy(options, options + 1);
		options++;
	}
	*options = chr;
}

static char	*opt_is_invalid(char *opt_str)
{
	if (!opt_str)
		return (NULL);
	while (*opt_str && ft_isalpha(*opt_str))
		opt_str++;
	if (*opt_str)
		return (opt_str);
	return (NULL);
}

char		*ft_optset(int *aargc, char ***aargv, char *opt_all)
{
	char	*opt_set;
	char	*ptr;
	char	*arg;

	if (opt_is_invalid(opt_all) || !(opt_set = ft_strnew(ft_strlen(opt_all))))
		return (NULL);
	ptr = opt_set;
	while (--(*aargc) && (arg = *(++(*aargv))) && arg[0] == '-' && arg[1])
	{
		if (!ft_strcmp(arg, "--") && ++(*aargv) && (--(*aargc) || *aargc))
			break ;
		while (*(++arg))
		{
			if (!ft_strchr(opt_all, *arg))
			{
				free(opt_set);
				return (NULL);
			}
			opt_append(opt_set, *arg);
		}
	}
	return (opt_set);
}
