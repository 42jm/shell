/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:30:26 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTYONESH_H
# define TWENTYONESH_H

# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>

# define MAX_INPUT_LENGTH 1025

char			**g_lines;
int				g_childret;
static char		*g_oparr[12] =
{
	";", "&",
	"&&", "||",
	"|",
	"<", ">", ">>", "<&", ">&", "<<",
	NULL
};

typedef struct	s_astnode
{
	char				*op;
	void				*content;
	struct s_astnode	*next;
}				t_astnode;

void			sighandle_ignore(int signum);

int				put_error(char *message, char *arg);
int				put_error_ret(char *message, char *arg, int ret);
int				put_prompt(int fd, t_list *envlst);
void			put_astlexed(t_astnode *node);
void			put_astparsed(t_astnode *node, size_t tabs);

size_t			ft_strclen_unquoted(char *s, char chr);
size_t			ft_stralen_unquoted(char *s, char *chars);
char			**ft_strcsplit_all(char *s, char c);
int				read_userinput(int fd, char ***input);
int				expand_word(t_astnode *node, t_list *envlst);
char			*parse_quotes(char *line);
size_t			quotationlen(char *s);
int				parse_userinput(char *line, t_astnode **aroot, t_list *envlst);
t_astnode		*token_new(char *type);
int				ast_parser(t_astnode **aroot);
int				ast_lexer(char *input, t_astnode **anode);
int				ast_execute(t_astnode **aroot, t_list *envlst);

size_t			astlex_oplen(char *ptr);

int				ast_localredir(t_astnode **at, t_list *envlst, int d, int s);
int				astexec_args(t_astnode *node, t_list *envlst);
int				astexec_simplecmd(t_astnode **anode, t_list *envlst);
int				astexec_redir(t_astnode **ahead, t_list *envlst);
int				astexec_andor(t_astnode **ahead, t_list *envlst);
int				astexec_semicol(t_astnode **at, t_list *envlst);
int				astexec_amper(t_astnode **at, t_list *envlst);
int				astexec_pipe(t_astnode **at, t_list *envlst);

char			**ast_to_strarr(t_astnode *node);

void			free_node(t_astnode *node);
void			free_ast(t_astnode *node);
void			free_lex(t_astnode *node);

int				test_file_validity(char *path);
int				test_file_existance(char *command, char **envp, char **apath);
int				get_command_path(char *command, char **envp, char **apath);
int				execute(char **args, t_list *envlst);

t_list			*env_getentry(t_list *envlst, char *varname);
char			*env_getvalue(t_list *envlst, char *varname);
int				env_set(t_list *envlst, char *varname, char *valnew);
int				env_unset(t_list *envlst, char *varname);
int				env_put(t_list *envlst);

int				builtin_echo(int argc, char **argv);
int				builtin_exit(int argc, char **argv);
int				builtin_cd(int argc, char **argv, t_list *envlst);
int				builtin_setenv(int argc, char **argv, t_list *envlst);
int				builtin_unsetenv(int argc, char **argv, t_list *envlst);
int				builtin_env(int argc, char **argv, t_list *envlst);
#endif
