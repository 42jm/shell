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

typedef struct	s_envvar
{
	bool	exportable;
	char	*name;
	char	*value;
}				t_envvar;
t_list			*g_envlst;

void			sighandle_ignore(int signum);

int				put_error(char *message, char *arg);
int				put_error_ret(char *message, char *arg, int ret);
int				put_prompt(int fd);
void			put_astlexed(t_astnode *node);
void			put_astparsed(t_astnode *node, size_t tabs);

size_t			ft_strclen_unquoted(char *s, char chr);
size_t			ft_stralen_unquoted(char *s, char *chars);
char			**ft_strcsplit_all(char *s, char c);
int				read_userinput(int fd, char ***input);
int				expand_tilde(t_astnode *node);
int				expand_param(t_astnode *node);
int				expand_word(t_astnode *node);
char			*parse_quotes(char *line);
size_t			quotationlen(char *s);
size_t			expansionlen(char *s);
t_astnode		*token_new(char *type);
int				token_delimit(t_astnode *token, char *input, size_t len);
int				handle_andor(t_astnode **at, t_astnode *prev, t_astnode *head);
int				ast_parser(t_astnode **aroot);
int				ast_lexer(char *input, t_astnode **anode);
int				ast_execute(t_astnode **aroot);

size_t			astlex_oplen(char *ptr);

int				ast_localredir(t_astnode **at, int dest, int src);
int				ast_localclose(t_astnode **at, int fd);
int				astredir_simple(t_astnode **at, int fd, char *op, char *path);
int				astredir_aggregate(t_astnode **at, int fd, char *op, char *word);
int				astredir_heredoc(t_astnode **at, int fd, char *op, char *word);

int				astexec_args(t_astnode *node);
int				astexec_simplecmd(t_astnode **anode);
int				astexec_redir(t_astnode **ahead);
int				astexec_andor(t_astnode **ahead);
int				astexec_semicol(t_astnode **at);
int				astexec_amper(t_astnode **at);
int				astexec_pipe(t_astnode **at);

char			**ast_to_strarr(t_astnode *node);

void			free_node(t_astnode *node);
void			free_ast(t_astnode *node);
void			free_lex(t_astnode *node);

int				test_file_validity(char *path);
int				test_file_existance(char *command, char **envp, char **apath);
int				get_command_path(char *command, char **envp, char **apath);
int				execute(char **args);

t_list			*env_getentry(char *varname);
char			*env_getvalue(char *varname);
int				env_set(char *varname, char *valnew, bool exportable);
int				env_unset(char *varname);
int				env_put(bool exportonly);
void			env_free(t_list *entry);
t_list			*env_splitnew(char *str, bool exportable);
t_list			*env_init(char **envp);
t_list			*env_strarr_to_struct(char **envp);
char			**env_struct_to_strarr(t_list *entry);

int				builtin_echo(int argc, char **argv);
int				builtin_exit(int argc, char **argv);
int				builtin_cd(int argc, char **argv);
int				builtin_setenv(int argc, char **argv);
int				builtin_unsetenv(int argc, char **argv);
int				builtin_env(int argc, char **argv);
#endif
