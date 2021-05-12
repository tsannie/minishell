/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/12 13:46:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			aff_dellnl(t_set *set)
{
	size_t		col;

	col = set->col;
	while (set->cur_pos - 12 < (int)(ft_strlen(set->str)))
	{
		if (((set->cur_pos + 1) % col) == 0)
		{
			ft_putstr_fd(set->tt_down, STDERR);
			while (--col > 0)
				ft_putstr_fd(set->tt_left, STDERR);
		}
		else
			ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
		col = set->col;
	}
	while (set->cur_pos > 12)
		ft_dell(set);
}

int				history_prev(t_set *set)
{
	if (set->his_pos > 0 && set->history[set->his_pos - 1])
		set->his_pos--;
	else
		return (0);
	aff_dellnl(set);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	ft_putstr_fd(set->str, STDERR);
	set->cur_pos = ft_strlen(set->str) + 12;
	return (0);
}

int				history_next(t_set *set)
{
	if (set->his_pos + 1 == set->inc_his)
	{
		aff_dellnl(set);
		ffree(set->str);
		set->str = ft_strdup("");
		set->cur_pos = ft_strlen(set->str) + 12;
		return (0);
	}
	if (set->his_pos < set->inc_his && set->history[set->his_pos + 1])
		set->his_pos++;
	else
		return (0);
	aff_dellnl(set);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	ft_putstr_fd(set->str, STDERR);
	set->cur_pos = ft_strlen(set->str) + 12;
	return (0);
}
