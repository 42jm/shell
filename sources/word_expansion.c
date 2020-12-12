/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static size_t	bashvar_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] == '_' || ft_isalnum(str[len]))
		len++;
	return (len);
}

static int	expand_param(t_astnode *node, t_list *envlst)
{
	char	*arg;
	char	*tmp;
	char	*var_value;
	size_t	var_i;
	size_t	var_len;

	arg = node->content;
	var_i = 0;
	while ((var_i = ft_strclen_unquoted(arg + var_i, '$')))
	{
		var_i--;
		if (!(var_len = bashvar_len(arg + var_i + 1)) && ++var_i)
			continue ;
		tmp = ft_strcrop(arg, var_i + 1, var_i + 1 + var_len);
		var_value = env_getvalue(envlst, tmp);
		free(tmp);
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

static int	expand_tilde(t_astnode *node, t_list *envlst)
{
	char	*home_path;
	char	*tmp;

	if (!node || !node->content)
		return (put_error("no arguments", "expand_tilde"));
	if (ft_strcmp(node->content, "~") && ft_strncmp(node->content, "~/", 2))
		return (0);
	home_path = env_getvalue(envlst, "HOME");
	if (!home_path)
		return (put_error("cannot find value of $HOME", "expand_tilde"));
	tmp = node->content;
	if (ft_strlen(node->content) == 1)
		node->content = ft_strdup(home_path);
	else
		node->content = ft_strjoin(home_path, (char *)node->content + 1);
	if (!node->content)
	{
		node->content = tmp;
		return (put_error("malloc failed", "expand_tilde"));
	}
	free(tmp);
	return (0);
}

static int	field_add(t_astnode *node, size_t n)
{
	t_astnode	*og_next;
	char		*og_word;

	og_next = node->next;
	og_word = node->content;
	node->content = ft_strndup(og_word, n - 1);
	if (!node->content)
	{
		node->content = og_word;
		return (put_error("malloc failed", "field_add"));
	}
	node->next = token_new(NULL);
	if (!node->next)
		return (put_error("failed to create new field", "field_add"));
	node->next->op = NULL;
	node->next->next = og_next;
	node->next->content = ft_strdup(og_word + n);
	if (!node->next->content)
	{
		node->next->content = og_word;
		return (put_error("malloc failed", "field_add"));
	}
	free(og_word);
	return (0);
}

static int	split_field(t_astnode *node, int *afields)
{
	size_t		len;
	int			ret;

	if (!node || !node->content || !afields)
		return (put_error("no arguments", "field_split"));
	len = ft_stralen_unquoted(node->content, "\t ");
	(*afields)++;
	if (!len)
		return (0);
	if ((ret = field_add(node, len)))
		return (ret);
	return (split_field(node->next, afields));
}

static int	remove_quotes(t_astnode *node)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	tmp = node->content;
	while ((len = ft_stralen_unquoted(tmp + i, "\"'\\")))
	{
		i += len - 1;
		len = 1;
		if (tmp[i] != '\\')
		{
			len = quotationlen(tmp + i);
			if (!len && ++i)
				continue ;
			if (ft_strdrop_inplace(&tmp, i + len - 1, i + len))
				return (put_error("malloc failed (closing)", "remove_quotes"));
			len -= 2;
		}
		if (ft_strdrop_inplace(&tmp, i, i + 1))
			return (put_error("malloc failed (opening)", "remove_quotes"));
		i += len;
	}
	node->content = tmp;
	return (0);
}

int			expand_word(t_astnode *node, t_list *envlst)
{
	int	ret;
	int	fields;

	while (node)
	{
		if (node->op)
		{
			node = node->next;
			continue ;
		}
		//1.1	~	tilde expansion
		if ((ret = expand_tilde(node, envlst)))
			return (ret);
		//1.2	$A	parameter expansion
		if ((ret = expand_param(node, envlst)))
			return (ret);
		//1.3	$()	command substitution
		//2			field splitting
		fields = 0;
		if ((ret = split_field(node, &fields)))
			return (ret);
		while (fields--)
		{
			//3		quote removal
			if ((ret = remove_quotes(node)))
				return (ret);
			node = node->next;
		}
	}
	return (0);
}
