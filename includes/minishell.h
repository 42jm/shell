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
# include <unistd.h>
# include <sys/wait.h>

# define MAX_INPUT_LENGTH 1025

extern char	**g_env;

int			put_error(char *message, char *arg);
int			put_error_ret(char *message, char *arg, int ret);
int			put_prompt(int fd);

int			read_userinput(int fd, char **input);
int			parse_userinput(char *line, char ***aargs);

int			test_file_validity(char *path);
int			test_file_existance(char *command, char **envp, char **apath);
int			get_command_path(char *command, char **envp, char **apath);
int			execute_any(char **args, t_list *envlst);

t_list		*env_getentry(t_list *envlst, char *varname);
char		*env_getvalue(t_list *envlst, char *varname);
int			env_set(t_list *envlst, char *varname, char *valnew);
int			env_unset(t_list *envlst, char *varname);
int			env_put(t_list *envlst);

int			builtin_echo(int argc, char **argv);
void		builtin_exit(int argc, char **argv);
int			builtin_cd(int argc, char **argv, t_list *envlst);
int			builtin_setenv(int argc, char **argv, t_list *envlst);
int			builtin_unsetenv(int argc, char **argv, t_list *envlst);
#endif
