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
	while (*opt_str && ft_isalnum(*opt_str))
		opt_str++;
	if (*opt_str)
		return (opt_str);
	return (NULL);
}

static char	*is_arg_opt(int *aargc, char ***aargv)
{
	char	*arg;

	(*aargc)--;
	if (!(*aargc))
	{
		(*aargv)++;
		return (NULL);
	}
	arg = *(++(*aargv));
	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (NULL);
	if (!ft_strcmp(arg, "--") && ++(*aargv) && (--(*aargc) || *aargc))
		return (NULL);
	return (arg);
}

char	*ft_optset(int *aargc, char ***aargv, char *opt_all)
{
	char	*opt_set;
	char	*ptr;
	char	*arg;

	if (opt_is_invalid(opt_all))
		return (NULL);
	opt_set = ft_strnew(ft_strlen(opt_all));
	if (!opt_set)
		return (NULL);
	ptr = opt_set;
	arg = is_arg_opt(aargc, aargv);
	while (arg)
	{
		while (*(++arg))
		{
			if (!ft_strchr(opt_all, *arg))
			{
				free(opt_set);
				return (NULL);
			}
			opt_append(opt_set, *arg);
		}
		arg = is_arg_opt(aargc, aargv);
	}
	return (opt_set);
}
