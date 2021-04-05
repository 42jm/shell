/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_get_ignored_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:33:47 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/02 18:45:04 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

void	get_ignored_signals(int *ignored_signals)
{
	int i;
	
	i = 0;
	ignored_signals[i++] = SIGQUIT;
	ignored_signals[i++] = SIGTERM;
	ignored_signals[i++] = SIGURG;
	ignored_signals[i++] = SIGTSTP;
	ignored_signals[i++] = SIGTTIN;
	ignored_signals[i++] = SIGTTOU;
	ignored_signals[i++] = 0;
}
