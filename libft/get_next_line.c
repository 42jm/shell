/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:36:23 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:15:47 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_first_lmnt(char *str_fd, t_list **lmnt, t_list **lst)
{
	char	**arr_fd;

	ERR_CHECK(!(arr_fd = (char **)malloc(2 * sizeof(char *))), NULL);
	ERR_CHECK(!(arr_fd[0] = ft_strdup(str_fd)), NULL);
	ERR_CHECK(!(arr_fd[1] = ft_strnew(0)), NULL);
	ERR_CHECK(!(*lmnt = ft_lstnew(arr_fd, 2 * sizeof(char *))), arr_fd);
	free(arr_fd);
	ft_lstadd(lst, *lmnt);
	return (1);
}

int	read_buff(int fd, char **line, t_list *lmnt)
{
	char	*buf;
	char	*str;
	int		sz;
	size_t	i;

	ERR_CHECK(!(buf = (char *)malloc(BUFF_SIZE + 1)), NULL);
	ft_bzero((void *)buf, BUFF_SIZE + 1);
	ERR_CHECK(((sz = read(fd, (void *)buf, BUFF_SIZE)) == -1), buf);
	ERR_CHECK(!(str = ft_strjoin(((char **)lmnt->content)[1], buf)), buf);
	free(((char **)lmnt->content)[1]);
	free(buf);
	i = ft_strclen(str, '\n');
	if (str[i] == '\n')
	{
		ERR_CHECK(!(((char **)lmnt->content)[1] = ft_strdup(str + i + 1)), str);
		ERR_CHECK(!(*line = ft_strndup(str, i)), str);
		free(str);
		return (1);
	}
	((char **)lmnt->content)[1] = str;
	if (sz > 0)
		return (get_next_line(fd, line));
	ERR_CHECK(!(*line = ft_strdup(str)), NULL);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	char			*fd_str;
	t_list			*lmnt;
	size_t			i;
	int				res;

	ERR_CHECK(fd < 0 || !(fd_str = ft_itoa(fd)), NULL);
	i = 0;
	if ((lmnt = lst))
		while (lmnt)
		{
			if (ft_strequ(((char **)lmnt->content)[0], fd_str))
				break ;
			i++;
			lmnt = lmnt->next;
		}
	ERR_CHECK((!lmnt && (get_first_lmnt(fd_str, &lmnt, &lst)) == -1), NULL);
	free(fd_str);
	if ((res = read_buff(fd, line, lmnt)))
		return (res);
	free(ft_lstpop(&lst, i));
	return ((*line && **line) ? 1 : 0);
}
