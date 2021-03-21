/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int2str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

char	*sig_int2str(int sig)
{
	size_t		i;
	static int	sig_intarr[] = {
		SIGABRT, SIGALRM, SIGBUS, SIGCHLD, SIGCLD, SIGCONT, \
		SIGFPE, SIGHUP, SIGILL, SIGINT, SIGIO, \
		SIGIOT, SIGKILL, SIGPIPE, SIGPOLL, SIGPROF, \
		SIGPWR, SIGQUIT, SIGSEGV, SIGSTKFLT, SIGSTOP, SIGTSTP, \
		SIGSYS, SIGTERM, SIGTRAP, SIGTTIN, SIGTTOU, \
		SIGURG, SIGUSR1, SIGUSR2, SIGVTALRM, SIGXCPU, SIGXFSZ, \
		SIGWINCH, 0};
	static char	*sig_strarr[] = {
		"SIGABRT", "SIGALRM", "SIGBUS", "SIGCHLD", "SIGCLD", "SIGCONT", \
		"SIGFPE", "SIGHUP", "SIGILL", "SIGINT", "SIGIO", \
		"SIGIOT", "SIGKILL", "SIGPIPE", "SIGPOLL", "SIGPROF", \
		"SIGPWR", "SIGQUIT", "SIGSEGV", "SIGSTKFLT", "SIGSTOP", "SIGTSTP", \
		"SIGSYS", "SIGTERM", "SIGTRAP", "SIGTTIN", "SIGTTOU", \
		"SIGURG", "SIGUSR1", "SIGUSR2", "SIGVTALRM", "SIGXCPU", "SIGXFSZ", \
		"SIGWINCH", NULL};

	i = ft_arrint(sig_intarr, sig);
	if (i < 0 || ft_strlen_arr((const char **)sig_strarr) <= i)
		return (NULL);
	return (ft_strdup(sig_strarr[i]));
}
