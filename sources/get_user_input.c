/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:00:55 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/20 23:15:25 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_current_char(char *buf, int *len)
{
	ft_bzero(buf, 16);
	*len = read(0, buf, 16);
	if (*len == -1)
	{
		ft_putstr("\nread() returned -1\n");
		return (NULL);
	}
	return (buf);
}

void	ft_input_init()

{
	ft_get_cursor_info();
	g_info.prompt = g_info.crsr_col;
	g_info.cursor = 0;
}

int		ft_key_interaction()
{
	char	chr[16];
	int		len;

	if (g_info.ctrl_c && !(g_info.ctrl_c &= 0))
		return (0);
	if (!ft_current_char(chr, &len))
		return (0);
	else if (len == 1)
		g_info.line = ft_size1_char(g_info.line, chr);
	else if (len == 3)
		ft_size3_char(chr);
	else if (len == 4)
		g_info.line = ft_size4_char(g_info.line, chr);
	else if (len == 6)
		ft_size6_char(chr);
	/*
	   else
	   ft_putchar_spe(chr);
	 */
	return (1);
}

char	*ft_str_first_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (ft_isprint(str[i]))
		i++;
	if (!(word = ft_memalloc(i + 1)))
		return (NULL);
	return (word = ft_strncpy(word, str, i));
}

int		ft_valid_hdoc(int i)
{
	char 	*eof;

	i += 2;
	while (g_info.line[i] == ' ' || g_info.line[i] == '\t')
		i++;
	eof = ft_str_first_word(&(g_info.line[i]));
	i += ft_strlen(eof) - 1;
	while (g_info.line[++i])
		if (!(ft_strncmp(&(g_info.line[i]), eof, ft_strlen(eof))))
		{
			free(eof);
			return (1);
		}
	free(eof);
	return (0);
}

int		ft_valid_quotes()
{
	int		i;

	i = -1;
	while (g_info.line[++i])
	{
		if (g_info.line[i] == '\'')
			while (g_info.line[++i] != '\'')
			{
				if (!g_info.line[i])
					return (0);
			}
		else if (g_info.line[i] == '\"')
			while (g_info.line[++i] != '\"')
			{
				if (!g_info.line[i])
					return (0);
			}
		else if (g_info.line[i] == '<' && g_info.line[i + 1] == '<')
			if (!ft_valid_hdoc(i))
				return (0);
	}
	return (1);
}

int		ft_line_validation()
{
	if (g_info.strlen && g_info.line[g_info.strlen - 1] == '\n')
	{
		if (!ft_valid_quotes())
			return (0);
		g_info.line[g_info.strlen - 1] = '\0';
		return (1);
	}
	return (0);
}

char	*ft_get_user_input()
{
	g_info.hist_pos = 0;
	g_info.strlen = 0;
	if (!(g_info.line = ft_memalloc(1)))
		return (NULL);
	ft_input_init();
	while (!ft_line_validation())
	{
		if (!ft_key_interaction())
		{
			free(g_info.line);
			return (NULL);
		}
	}
	/*
	   if (ft_strstr("<<", g_info.line) && !ft_strextended())
	   return
	 */
	if (!(g_info.hist = ft_history_new()))
		return (NULL);
	return (g_info.line);
}

void	ft_end_clean(char *end_message)
{
	if (tcsetattr(0, 0, &(g_info.s_termios_backup)) == -1)
		ft_putstr("\nerror: can't recover terminal configuration:\
			tcsetattr() returned -1\n");
	ft_free_tabzero(g_info.hist);
	if (g_info.copy)
		free(g_info.copy);
	if (end_message)
		ft_putstr(end_message);
}

/*
int		main(int ac, char **av)
{
	char			*str;

	(void)av;
	if (ac == 1)
	{
		if (!ft_start_up())
			return (-1);
//		chk21();
		ft_putchar('\n');
		while ("LOOP!")
		{
			ft_putstr("\\_$> ");
			if (!(str = ft_get_user_input(&g_info)))
				break ;
			if (!ft_strncmp("exit", str, 3))
				break ;
		}
		ft_ctrl_e();
		ft_putstr("\n_____\n");
		ft_display_history();
		ft_end_clean("");
	}
	else
		ft_putstr("Too many arguments\n");
	return (0);
}
*/
