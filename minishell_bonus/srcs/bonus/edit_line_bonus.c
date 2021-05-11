/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/11 15:48:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			go_g(t_set *set)
{
	if (set->cur_pos - 13 > 0 && set->str[set->cur_pos - 12] != ' ' &&
	set->str[set->cur_pos - 13] == ' ')
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

void			go_d(t_set *set)
{
	int col;

	col = set->col;
	while (set->cur_pos < (int)(ft_strlen(set->str) + 12) && set->str[set->cur_pos - 12] != ' ')
	{
		if (((set->cur_pos + 1) % col) == 0)
		{
			ft_putstr_fd(set->tt_down, STDERR);
			while (--col >= 0)
				ft_putstr_fd(set->tt_left, STDERR);
		}
		col = set->col;
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
	while (set->cur_pos < (int)(ft_strlen(set->str) + 12) && set->str[set->cur_pos - 12] == ' ')
	{
		if (((set->cur_pos + 1) % col) == 0)
		{
			ft_putstr_fd(set->tt_down, STDERR);
			while (--col >= 0)
				ft_putstr_fd(set->tt_left, STDERR);
		}
		col = set->col;
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
}


void			fg_o_fd(t_set *set, int x)
{
	int col;
	int len;
	int r;

	r = 0;
	len = set->cur_pos;
	col = set->col;
	if ((x == 70 || x == 67 || x == 65) && set->cur_pos - 12 < (int)(ft_strlen(set->str)))
	{
		if (((len + 1) % col) == 0)
		{
			ft_putstr_fd(set->tt_down, STDERR);
			while (--col > 0)
				ft_putstr_fd(set->tt_left, STDERR);
		}
		else
			ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
	else if ((x == 72 || x == 68 || x == 66) && set->cur_pos -12 > 0)
	{
		if ((len % col) == 0)
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

void			go_home(t_set *set, char *buf)
{
	while (set->cur_pos - 12 < (int)(ft_strlen(set->str)))
		fg_o_fd(set, buf[2]);
}

void			go_end(t_set *set, char *buf)
{
	while (set->cur_pos -12 > 0)
		fg_o_fd(set, buf[2]);
}

void			go_up(t_set *set)
{
	int i = 0;

	while(i < set->col)
	{
		fg_o_fd(set, 66);
		i++;
	}
}

void			go_down(t_set *set)
{
	int i = 0;

	while(i < set->col)
	{
		fg_o_fd(set, 65);
		i++;
	}
}

int				set_fle(t_set *set, char *buf)
{
	signal(SIGINT, SIG_IGN);
	if (buf[1] == 91)
	{
		if (buf[2] == 65)
			history_prev(set);
		else if (buf[2] == 66)
			history_next(set);
		else if (buf[2] == 70)
			go_home(set, buf);
		else if (buf[2] == 72)
			go_end(set, buf);
		else if (buf[2] == 49 && buf[5] == 68)
			go_g(set);
		else if (buf[2] == 49 && buf[5] == 67)
			go_d(set);
		else if (buf[2] == 49 && buf[5] == 65)
			go_up(set);
		else if (buf[2] == 49 && buf[5] == 66)
			go_down(set);
		else
			fg_o_fd(set, buf[2]);
		free_buff(buf);
	}
	return (0);
}