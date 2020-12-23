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
	return (ft_strdup(value));
}

static int	expand_substitute(char **aarg, size_t *avar_i)
{
	int		ret;
	size_t	len;
	char	*in;
	char	*out;
	char	*tmp;

	if (!(len = parenlen(*aarg + *avar_i + 1)))
		return (put_error("bad argument", "expand_subsitute"));
	if (!(in = ft_strndup(*aarg + *avar_i + 2, len - 2)))
		return (put_error("malloc failed", "expand_substitute"));
	out = NULL;
	ret = exec_str_in_subshell(in, &out);
	free(in);
	if (ret)
		return (ret);
	if (out && out[ft_strlen(out) - 1] == '\n')
		out[ft_strlen(out) - 1] = '\0';
	tmp = ft_strreplace(*aarg, out, *avar_i, *avar_i + len + 1);
	if (!tmp)
		return (put_error("str replace call failed", "expand_substitute"));
	free(*aarg);
	*aarg = tmp;
	*avar_i += ft_strlen(out);
	free(out);
	return (0);
}

static int	expand_variable(char **aarg, size_t *avar_i)
{
	char	*arg;
	size_t	var_i;
	size_t	var_len;
	char	*var_value;
	char	*tmp;

	arg = *aarg;
	var_i = *avar_i;
	if (!(var_len = bashvar_len(arg + var_i + 1)) && ++(*avar_i))
		return (0);
	if (arg[var_i + 1] == '{' && arg[var_i + 2] == '}')
		return (put_error("bad substitution", "${}"));
	var_value = param_getvalue(arg + var_i + 1, var_len);
	if (!(tmp = ft_strreplace(arg, var_value, var_i, var_i + var_len + 1)))
		return (put_error("str replace call failed", "expand_param"));
	free(arg);
	arg = tmp;
	var_i += ft_strlen(var_value);
	free(var_value);
	*avar_i = var_i;
	*aarg = arg;
	return (0);
}

int			expand_param(t_astnode *node)
{
	char	*arg;
	size_t	var_i;
	int		ret;

	if (!node->content)
		return (0);
	arg = node->content;
	var_i = 0;
	while ((var_i = ft_strclen_unquoted(arg + var_i, '$', "\\'")))
	{
		var_i--;
		if (arg[var_i + 1] == '(')
			ret = expand_substitute(&arg, &var_i);
		else
			ret = expand_variable(&arg, &var_i);
		if (ret)
			return (ret);
	}
	node->content = arg;
	return (0);
}
