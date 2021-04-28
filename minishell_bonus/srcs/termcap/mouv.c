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

void		aff_dellnl(size_t len, size_t col, t_set *set)
{
	while (len > 0)
	{
		if (((len) % col) == 0)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			ft_putstr_fd("\033[2K", STDERR);
		}
		else
		{
			ft_putstr_fd(set->tt_left, STDERR);
			ft_putstr_fd(" ", STDERR);
			ft_putstr_fd(set->tt_left, STDERR);
		}
		len--;
	}
}

int			history_prev(t_set *set)
{
	size_t len;
	size_t col;

	col = set->col;
	set->dell_his = 0;
	len = ft_strlen(set->str) + 12;
	if (set->his_pos > 0 && set->history[set->his_pos - 1])
		set->his_pos--;
	else
		return (0);
	set->dell_his = getdellen(ft_strlen(set->str), col);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	aff_dellnl(len, col, set);
	ft_putstr_fd("\033[2K", STDERR);
	disp_prompt();
	ft_putstr_fd(set->str, STDERR);
	return (0);
}

int			history_next(t_set *set)
{
	size_t len;
	size_t col;

	col = set->col;
	len = ft_strlen(set->str) + 12;
	if (set->his_pos < set->inc_his && set->history[set->his_pos + 1])
		set->his_pos++;
	else
		return (0);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	set->dell_his = getdellen(ft_strlen(set->str), set->col);
	aff_dellnl(len, col, set);
	ft_putstr_fd("\033[2K", STDERR);
	disp_prompt();
	ft_putstr_fd(set->str, STDERR);
	return (0);
}
