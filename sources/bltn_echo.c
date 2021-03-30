/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/03/30 20:24:23 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int 	ft_octal_char(char *chr)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (chr[++i] && i <= 3 && '0' <= chr[i] && chr[i] <= '7')
		c = c * 8 + (chr[i] - '0');
	ft_putchar(c);
	return (i);
}

void	ft_special_char(char c)
{
	if (c == 'a')
		c = '\a';
	else if (c == 'b')
		c = '\b';
	else if (c == 't')
		c = '\t';
	else if (c == 'n')
		c = '\n';
	else if (c == 'v')
		c = '\v';
	else if (c == 'f')
		c = '\f';
	else if (c == 'r')
		c = '\r';
	else if (c == '\\')
		c = '\\';
	ft_putchar(c);
}

int 	ft_char_sequence(char *chr, int *nl)
{
	int	i;

	i = 1;
	if (chr[i] == 'c')
	{
		*nl = 0;
		while (chr[i])
			i++;
	}
	else if (ft_strchr("\\abtnvfr", chr[i]))
		ft_special_char(chr[i++]);
	else if (chr[i] == '0')
		i += ft_octal_char(&chr[i]);
	else
		ft_putchar('\\');
	return (i);
}

void	ft_echo(char *str, int *nl)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += ft_char_sequence(&str[i], nl);
		else
			ft_putchar(str[i++]);
	}
}

int	builtin_echo(int argc, char **argv)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (argc > 1 && !ft_strcmp("-n", argv[i]))
	{
		nl = 0;
		i++;
	}
	while (i < argc)
	{
		ft_echo(argv[i], &nl);
		if (++i < argc)
			pr_putstr_fd(" ", 1);
	}
	if (nl)
		pr_putstr_fd("\n", 1);
	return (0);
}
