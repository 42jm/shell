/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_ignore_signals_during_command_execution        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:21:52 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/05 16:52:56 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

static void	get_other_signals(int *other_signals)
{
	int	i;

	i = 0;
	other_signals[i++] = SIGINT;
	other_signals[i++] = SIGCONT;
	other_signals[i++] = SIGCHLD;
	other_signals[i++] = 0;
}

void	ignore_signal_during_command_execution(void)
{
	struct sigaction *action;
	int core_signals[10];
	int	term_signals[9];
	int	other_signals[4];

	get_core_signals(core_signals);
	get_term_signals(term_signals);
	get_other_signals(other_signals);
	action = ft_memalloc(sizeof(struct sigaction));
	action->sa_handler = SIG_IGN;
	action->sa_flags = SA_RESTART;
	sigfillset(&action->sa_mask);
	set_up_action_for_given_signals(core_signals, action);
	set_up_action_for_given_signals(term_signals, action);
	set_up_action_for_given_signals(other_signals, action);
}