/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 12:16:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			go_gg(t_set *set)
{
	while (set->cur_pos > 12 && set->str[set->cur_pos - 12] != ' ')
	{
		ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
	while (set->cur_pos > 12 && set->str[set->cur_pos - 12] == ' ')
	{
		ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
	while (set->cur_pos > 12 && set->str[set->cur_pos - 12] != ' ')
	{
		ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
}

void			go_g(t_set *set)
{
	if (set->cur_pos - 13 > 0 && set->str[set->cur_pos - 12] != ' ' &&
	set->str[set->cur_pos - 13] == ' ')
		go_gg(set);
	else if (set->cur_pos - 13 > 0 && set->str[set->cur_pos - 12] != ' ' &&
	set->str[set->cur_pos - 13] != ' ')
	{
		while (set->cur_pos > 12 && set->str[set->cur_pos - 12] != ' ')
		{
			ft_putstr_fd(set->tt_left, STDERR);
			set->cur_pos--;
		}
	}
	if (set->cur_pos != 12)
	{
		set->cur_pos++;
		ft_putstr_fd(set->tt_right, STDERR);
	}
}

void			new_line(t_set *set, int col)
{
	ft_putstr_fd(set->tt_down, STDERR);
	while (--col >= 0)
		ft_putstr_fd(set->tt_left, STDERR);
}

void			go_d(t_set *set, int col)
{
	while (set->cur_pos < (int)(ft_strlen(set->str) + 12) &&
	set->str[set->cur_pos - 12] != ' ')
	{
		if (((set->cur_pos + 1) % col) == 0)
			new_line(set, col);
		col = set->col;
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
	while (set->cur_pos < (int)(ft_strlen(set->str) + 12)
	&& set->str[set->cur_pos - 12] == ' ')
	{
		if (((set->cur_pos + 1) % col) == 0)
			new_line(set, col);
		col = set->col;
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
}

void			fg_o_fd(t_set *set, int x, int r, int col)
{
	if ((x == 70 || x == 67 || x == 65) &&
	set->cur_pos - 12 < (int)(ft_strlen(set->str)))
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
	}
	else if ((x == 72 || x == 68 || x == 66) && set->cur_pos - 12 > 0)
	{
		if ((set->cur_pos % col) == 0)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			while (++r < col)
				ft_putstr_fd(set->tt_right, STDERR);
		}
		else
			ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
}
