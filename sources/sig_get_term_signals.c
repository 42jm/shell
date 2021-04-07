/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_get_term_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:26:05 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/07 09:19:35 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

void	get_term_signals(int *term_signals)
{
	int	i;

	i = 0;
	term_signals[i++] = SIGHUP;
	term_signals[i++] = SIGPIPE;
	term_signals[i++] = SIGALRM;
	term_signals[i++] = SIGPOLL;
	term_signals[i++] = SIGVTALRM;
	term_signals[i++] = SIGPROF;
	term_signals[i++] = SIGUSR1;
	term_signals[i++] = SIGUSR2;
	term_signals[i++] = 0;
}
