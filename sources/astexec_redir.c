/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astexec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	ast_localclose(t_astnode **at, t_list *envlst, int fd)
{
	int	tmp;
	int	ret;

	if ((tmp = dup(fd)) == -1)
		return (put_error("failed to store fd", "localclose"));
	if (close(fd) == -1)
		return (put_error("failed to close fd", "localclose"));
	ret = ast_execute(at, envlst);
	if (dup2(tmp, fd) == -1)
		return (put_error("failed to restore fd", "localclose"));
	if (close(tmp) == -1)
		return (put_error("failed to close tmp fd", "localclose"));
	return (ret);
}

int	ast_localredir(t_astnode **at, t_list *envlst, int dst, int src)
{
	int	tmp_src;
	int	ret;

	if ((tmp_src = dup(src)) == -1)
		return (put_error("failed to store source fd", "localredir"));
	if (dup2(dst, src) == -1)
		return (put_error("failed to replace source fd", "localredir"));
	ret = ast_execute(at, envlst);
	if (dup2(tmp_src, src) == -1)
		return (put_error("failed to restore source fd", "localredir"));
	if (close(tmp_src) == -1)
		return (put_error("failed to close tmp fd", "localredir"));
	return (ret);
}

int	astredir_simple(t_astnode **at, t_list *envlst, int redir_fd, char *redir_op, char *path)
{
	int		word_fd;
	int		flags;
	mode_t	rights;

	if (!redir_op || !path)
		return (put_error("no arguments", "astredir_simple"));
	if (!ft_strcmp(redir_op, "<"))
		flags = O_RDONLY;
	if (!ft_strcmp(redir_op, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (!ft_strcmp(redir_op, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if ((word_fd = open(path, flags, rights)) == -1)
		return (put_error("failed to open file", path));
	return (ast_localredir(at, envlst, word_fd, redir_fd));
}

int	astredir_aggregate(t_astnode **at, t_list *envlst, int redir_fd, char *redir_op, char *word)
{
	char	*ptr;

	if (!redir_op || !word || !*word)
		return (put_error("no arguments", "astredir_aggregate"));
	if (!ft_strcmp(word, "-"))
		return (ast_localclose(at, envlst, redir_fd));
	ptr = word;
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr)
		return (put_error("word following redir_op is not a number", redir_op));
	return (ast_localredir(at, envlst, ft_atoi(word), redir_fd));
}

int	astredir_heredoc(t_astnode **at, t_list *envlst, int fd, char *redir_op, char *word)
{
	//char	*str;
	//char	*tmp;
	int		fildes[2];
	pid_t	pid;
	int		ret;

	if (!g_lines || !*g_lines)
		return (put_error("no arguments", "astredir_heredoc"));
	//str = NULL;
	/*
	while (*g_lines && ft_strcmp(*g_lines, word))
	{
		if (!str)
			tmp = ft_strdup(*g_lines);
		else
			tmp = ft_strcjoin('\n', str, *g_lines);
		if (!tmp)
		{
			if (str)
				free(str);
			return (put_error("malloc failed", "astredir_heredoc"));
		}
		if (str)
			free(str);
		str = tmp;
		g_lines++;
	}
	if (!*g_lines)
	{
		if (str)
			free(str);
		return (put_error("delimiter word not found", redir_op));
	}
	g_lines++;
	*/
	/*
	if (fd == 0)
		ft_putendl("					FD == 0");
	if (str)
	{
		ft_putstr("// DEBUG: heredoc: ");
		ft_putstr(str);
	}
	*/
	if (pipe(fildes) == -1)
		return (put_error("pipe failed", redir_op));
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sighandle_ignore);
		if (close(fildes[0]) == -1)
			return (put_error("child failed to close pipe (read)", "heredoc"));

		while (*g_lines)
		{
			if (!ft_strcmp(*g_lines, word))
				break ;
			ft_putendl_fd(*g_lines, fildes[1]);
			g_lines++;
		}
		if (*g_lines && !ft_strcmp(*g_lines, word))
			g_lines++;
		else
			return (put_error("delimitor word not found", word));
		/*
		if (str && (write(fildes[1], str, ft_strlen(str)) == -1 || write(fildes[1], "\n", 1) == -1))
		{
			if (str)
				free(str);
			return (put_error("child failed to write", redir_op));
		}
		*/
		if (close(fildes[1]) == -1)
			return (put_error("child failed to close pipe (write)", "heredoc"));
		return (-1);
	}
	if (close(fildes[1]) == -1)
		return (put_error("parent failed to close pipe write side", "heredoc"));
	ret = ast_localredir(at, envlst, fildes[0], fd);
	if (close(fildes[0]) == -1)
		return (put_error("parent failed to close pipe read side", "heredoc"));
	while (*g_lines && ft_strcmp(*g_lines, word))
		g_lines++;
	if (*g_lines && !ft_strcmp(*g_lines, word))
		g_lines++;
	return (ret);
}

char	*astget_redirop(char *op)
{
	if (!op)
		return (NULL);
	while (ft_isdigit(*op))
		op++;
	if (!ft_strcmp(op, "<") || !ft_strcmp(op, ">") || !ft_strcmp(op, ">>") \
	|| !ft_strcmp(op, "<&") || !ft_strcmp(op, ">&") \
	|| !ft_strcmp(op, "<<"))
		return (op);
	return (NULL);
}

int		astredir_handler(t_astnode **at, t_list *envlst, t_astnode *node)
{
	char	*redir_op;
	char	*word;
	int		fd;

	if (!node || !node->op)
		return (put_error("no arguments", "astredir_handler"));
	if (!(redir_op = astget_redirop(node->op)))
		return (put_error("node is not a redir_op", node->op));
	if (!node->next || node->next->op)
		return (put_error("no word following redir_op", redir_op));
	word = node->next->content;
	fd = 0;
	if (ft_isdigit(*node->op))
		fd = ft_atoi(node->op);
	else if (*redir_op == '>')
		fd = 1;
	if (!ft_strcmp(redir_op, "<") \
	|| !ft_strcmp(redir_op, ">") \
	|| !ft_strcmp(redir_op, ">>"))
		return (astredir_simple(at, envlst, fd, redir_op, word));
	else if (!ft_strcmp(redir_op, "<&") \
	|| !ft_strcmp(redir_op, ">&"))
		return (astredir_aggregate(at, envlst, fd, redir_op, word));
	else if (!ft_strcmp(redir_op, "<<"))
		return (astredir_heredoc(at, envlst, fd, redir_op, word));
	return (put_error("invalid redirection operator", redir_op));
}

int		astpop_redir(t_astnode **ahead, t_astnode **aredir)
{
	t_astnode	*node;
	t_astnode	*prev;

	*aredir = NULL;
	node = *ahead;
	prev = NULL;
	while (node && !astget_redirop(node->op))
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return (0);
	if (!node->next || node->next->op)
		return (put_error("no words directly after redir_op", node->op));
	if (prev)
		prev->next = node->next->next;
	else
		*ahead = node->next->next;
	node->next->next = NULL;
	*aredir = node;
	return (0);
}

int		astexec_redir(t_astnode **ahead, t_list *envlst)
{
	t_astnode	*node;
	int			ret;

	if (!ahead)
		return (put_error("no arguments", "astexec_redir"));
	node = NULL;
	if ((ret = astpop_redir(ahead, &node)))
		return (ret);
	if (!node)
		return (astexec_args(*ahead, envlst));
	ret = astredir_handler(ahead, envlst, node);
	free_node(node->next);
	free_node(node);
	return (ret);
}
