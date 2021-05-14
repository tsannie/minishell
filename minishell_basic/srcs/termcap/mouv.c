/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 10:38:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

void		aff_last_buf(t_set *set, char *buf)
{
	if ((((int)ft_strlen(set->str) + 12) % (set->col)) == 0)
	{
		ft_putstr_fd(buf, STDERR);
		aff_dell(set);
	}
}

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

void		aff_all_h(t_set *set)
{
	disp_prompt();
	ft_putstr_fd(set->str, STDERR);
	if ((((int)ft_strlen(set->str) + 12) % (set->col)) == 0)
	{
		ft_putstr_fd(" ", STDERR);
		aff_dell(set);
	}
}

int			history_prev(t_set *set)
{
	size_t len;
	size_t col;

	col = set->col;
	len = ft_strlen(set->str) + 12;
	if (set->his_pos > 0 && set->history[set->his_pos - 1])
		set->his_pos--;
	else
		return (0);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	aff_dellnl(len, col, set);
	ft_putstr_fd("\033[2K", STDERR);
	aff_all_h(set);
	return (0);
}

int			history_next(t_set *set)
{
	size_t len;
	size_t col;

	col = set->col;
	len = ft_strlen(set->str) + 12;
	if (set->his_pos + 1 == set->inc_his)
	{
		ffree(set->str);
		set->str = ft_strdup("");
		aff_dellnl(len, col, set);
		ft_putstr_fd("\033[2K", STDERR);
		disp_prompt();
		return (0);
	}
	if (set->his_pos < set->inc_his && set->history[set->his_pos + 1])
		set->his_pos++;
	else
		return (0);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	aff_dellnl(len, col, set);
	ft_putstr_fd("\033[2K", STDERR);
	aff_all_h(set);
	return (0);
}
