/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_action_for_given_signals.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:01:54 by lgaveria          #+#    #+#             */
/*   Updated: 2021/04/02 18:02:08 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_42sh.h"

void set_up_action_for_given_signals(int *signals, struct sigaction *action)
{
	int	i;

	i = 0 ;
	while (signals[i])
	{
		sigaction(signals[i], action, NULL);
		i++;
	}
}
