/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

size_t		bashvar_len(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	if (ft_strchr("#?", *str))
		return (1);
	if (*str == '{')
		return (ft_strclen(str, '}'));
	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	while (!ft_isdigit(*str) && (str[len] == '_' || ft_isalnum(str[len])))
		len++;
	return (len);
}

static char	*param_getvalue(char *str, size_t len)
{
	char	*name;
	char	*value;

	if (*str == '{')
	{
		name = ft_strcdup(str + 1, '}');
		if (!name)
			return (NULL);
	}
	else
		name = ft_strndup(str, len);
	value = env_getvalue(name);
	free(name);
	return (value);
}

int			expand_param(t_astnode *node)
{
	char	*arg;
	char	*tmp;
	char	*var_value;
	size_t	var_i;
	size_t	var_len;

	arg = node->content;
	var_i = 0;
	while ((var_i = ft_strclen_unquoted(arg + var_i, '$', "\\'")))
	{
		var_i--;
		if (!(var_len = bashvar_len(arg + var_i + 1)) && ++var_i)
			continue ;
		if (arg[var_i + 1] == '{' && arg[var_i + 2] == '}')
			return (put_error("bad substitution", "${}"));
		var_value = param_getvalue(arg + var_i + 1, var_len);
		tmp = ft_strreplace(arg, var_value, var_i, var_i + var_len + 1);
		if (!tmp)
			return (put_error("str replace call failed", "expand_param"));
		free(arg);
		arg = tmp;
		var_i += ft_strlen(var_value);
	}
	node->content = arg;
	return (0);
}
