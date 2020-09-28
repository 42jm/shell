/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/11/01 17:56:32 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/wait.h>

# define MAX_INPUT_LENGTH 1025

extern char	**environ;
extern char	**g_env;

int			put_prompt(int fd);
int			read_userinput(int fd, char **input);
int			parse_userinput(char *line, char ***aargs);
int			execute_command(char **args, t_list *envlst);
int			put_error(char *message, char *arg);
int			put_error_ret(char *message, char *arg, int ret);
char		*env_getvalue(t_list *envlst, char *varname);
int			builtin_echo(int argc, char **argv);
void		builtin_exit(int argc, char **argv);
int			builtin_cd(int argc, char **argv, t_list *envlst);
#endif
