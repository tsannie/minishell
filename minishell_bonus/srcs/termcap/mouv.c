/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			aff_dellnl(t_set *set)
{
	size_t		col;
	int			e;

	e = 0;
	col = set->col;
	while (set->cur_pos - 12 < ft_strlen(set->str))
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
	size_t		len;
	size_t		col;
	int			e;

	e = 0;
	col = set->col;
	set->dell_his = 0;
	len = ft_strlen(set->str) + 12;
	if (set->his_pos > 0 && set->history[set->his_pos - 1])
		set->his_pos--;
	else
		return (0);
	aff_dellnl(set);
	set->dell_his = getdellen(ft_strlen(set->str), col);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	ft_putstr_fd(set->str, STDERR);
	set->cur_pos = ft_strlen(set->str) + 12;
	return (0);
}

int				history_next(t_set *set)
{
	size_t		len;
	size_t		col;
	int			e;

	e = 0;
	col = set->col;
	len = ft_strlen(set->str);
	if (set->his_pos < set->inc_his && set->history[set->his_pos + 1])
		set->his_pos++;
	else
		return (0);
	aff_dellnl(set);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	set->dell_his = getdellen(ft_strlen(set->str), set->col);
	ft_putstr_fd(set->str, STDERR);
	set->cur_pos = ft_strlen(set->str) + 12;
	return (0);
}
