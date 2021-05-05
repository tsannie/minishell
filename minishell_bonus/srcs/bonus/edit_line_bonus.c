/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/29 15:16:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			go_home(t_set *set, char *buf)
{
	size_t len;

	len = ft_strlen(set->str);
	while (set->cur_pos > 12)
	{
		ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
}

void			go_end(t_set *set, char *buf)
{
	size_t len;

	len = ft_strlen(set->str);
	while (set->cur_pos < (ft_strlen(set->str) + 12))
	{
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
}

void			go_g(t_set *set, char *buf)
{
	int pos;
	size_t len;

	len = ft_strlen(set->str);
	pos = set->cur_pos;
	//ft_bzero((void *)buf, BUF_SIZE);
	//buf[0] = 0;
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

void			go_d(t_set *set, char *buf)
{
	int pos;
	size_t len;

	len = ft_strlen(set->str);
	pos = set->cur_pos;
	//ft_bzero((void *)buf, BUF_SIZE);
	//buf[0] = 0;
	while (set->cur_pos < (ft_strlen(set->str) + 12) && set->str[set->cur_pos - 12] != ' ')
	{
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
	while (set->cur_pos < (ft_strlen(set->str) + 12) && set->str[set->cur_pos - 12] == ' ')
	{
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
}

void			fg_o_fd(t_set *set, char *buf)
{
	int col;
	int len;
	int r;

	r = 0;
	len = set->cur_pos;
	col = set->col;
	if (buf[2] == 67 && set->cur_pos - 12 < ft_strlen(set->str))
	{
		//printf("[%d][%d][%d]\n", len, col, len % col);
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
	else if (buf[2] == 68 && set->cur_pos -12 > 0)
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
			go_g(set, buf);
		else if (buf[2] == 49 && buf[5] == 67)
			go_d(set, buf);
		fg_o_fd(set, buf);
		free_buff(buf);
	}
	return (0);
}