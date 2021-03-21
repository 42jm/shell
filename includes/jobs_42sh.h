/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_42sh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:39:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/01/28 22:17:50 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_42SH_H
# define JOBS_42SH_H

# include "header_42sh.h"
# include <termios.h>

/*
** __________
** STRUCTURES
**
**		s_job
**	pgid		process group id of all processes under this job
**	tmodes		backup of the job terminal modes
**	foreground	true if in foreground, false if in background
**	command		the command string describing the job
**	status		string describing the job's state
**	nbr			indentifier used by builtins
*/
typedef struct s_job
{
	pid_t			pgid;
	struct termios	tmodes;
	int				foreground;
	char			*command;
	char			*status;
	int				nbr;
	int				notified;
}	t_job;

/*
**		s_shell	
**	pgid			shell process group id
**	joblst			list of all jobs
**	tmodes			backup of shell initial terminal modes
**	terminal		terminal fd, equivalent of initial STDIN_FILENO
**	is_subshell		starts at 0. subshells should increment it
**	is_interactive	isatty(STDIN_FILENO) at startup, set to 0 if subshell
**	inside_job		true if the shell is currently executing a job
*/
typedef struct s_shell
{
	pid_t			pgid;
	t_list			*joblst;
	struct termios	tmodes;
	int				terminal;
	int				is_subshell;
	int				is_interactive;
	int				inside_job;
}	t_shell;

/*
** ________________
** GLOBAL VARIABLES
**
**	g_shell		used to implement job control
*/
extern t_shell	*g_shell;

/*
** ______________
** INITIALISATION
**
**	job_init_shell()	mallocs g_shell, ignore stop signals, sets pgid to pid
**	job_start_new()		create a new job and set it as current
*/
int		job_init_shell(void);
int		job_start_new(t_astnode *node);

/*
**		job_launch.c
*/
int		job_init_process(t_job *job);
int		put_job_in_foreground(t_job *job, int cont);
int		put_job_in_background(t_job *job, int cont);

/*
**		job_notifs.c
*/
int		job_notify(t_job *job, int unnotified_only, char option, int fd);

/*
**		job_update.c
*/
int		job_update_status(pid_t pgid, int status);

/*
**		job_wait.c
*/
int		job_wait(t_job *job);
int		exejob_wait(pid_t pid);

/*
** ____
** FREE
**
**		job_cleanup.c
**	job_cleanup()		free nth job or finished jobs if nbr == 0
*/
int		job_cleanup(int nbr);

/*
** _______
** HELPERS
**
**		job_gets.c			contains job finding functions
**	jobget_pgid()		find job from pgid
**	jobget_jobid()		find job from posix job_id
*/
t_job	*jobget_pgid(pid_t pgid);
t_job	*jobget_jobid(char *job_id);

/*
** ________
** BUILTINS
**
**		bltn_jobs.c
**	builtin_jobs()	lists jobs
**	builtin_fg()	puts a job in foreground
**	builtin_bg()	puts a job in background
*/
int		builtin_jobs(int argc, char **argv);
int		builtin_fg(int argc, char **argv);
int		builtin_bg(int argc, char **argv);

/*
** __________________
** CONVERT AST TO STR
**
**		job_ast2str.c		main file
**	job_ast2str()	calling function, wrapper for main function
**	astcmdstr()		main function, calls op dispatcher or handles word nodes
**	astcmdstr_cpy()	adds str argument to buffer, then updates buffer
*/
char	*job_ast2str(t_astnode *head);
int		astcmdstr(t_astnode *node, char **acmd);
int		astcmdstr_cpy(char **acmd, char *str);

/*
**		job_ast2str_op.c	operator handlers
**	..op_after()	put order: contents,	op,			next
**	..op_before()	put order: op,			contents,	next
**	..op_around()	put order: op_left,		contents,	op_right,	next
**	..op_ignore()	put order: contents,	next
**	..op_heredoc()	put order: op,			next,		heredoc,	word_delim
*/
int		astcmdstr_op_after(t_astnode *node, char **acmd);
int		astcmdstr_op_before(t_astnode *node, char **acmd);
int		astcmdstr_op_around(t_astnode *node, char **acmd);
int		astcmdstr_op_ignore(t_astnode *node, char **acmd);
int		astcmdstr_op_heredoc(t_astnode *node, char **acmd);

/*
**		job_ast2str_get.c	helpers for operator handlers
**	..braces()		op_around helper: return relevent op_left and op_right
*/
void	oparound_get_braces(char *op, char **left, char **right);

#endif
