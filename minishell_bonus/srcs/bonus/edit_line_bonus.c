/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 12:16:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			go_home(t_set *set, char *buf)
{
	while (set->cur_pos - 12 < (int)(ft_strlen(set->str)))
		fg_o_fd(set, buf[2], 0, set->col);
}

void			go_end(t_set *set, char *buf)
{
	while (set->cur_pos - 12 > 0)
		fg_o_fd(set, buf[2], 0, set->col);
}

void			go_up(t_set *set)
{
	int			i;

	i = 0;
	while (i < set->col)
	{
		fg_o_fd(set, 66, 0, set->col);
		i++;
	}
}

void			go_down(t_set *set)
{
	int			i;

	i = 0;
	while (i < set->col)
	{
		fg_o_fd(set, 65, 0, set->col);
		i++;
	}
}

int				set_fle(t_set *set, char *buf)
{
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
			go_d(set, set->col);
		else if (buf[2] == 49 && buf[5] == 65)
			go_up(set);
		else if (buf[2] == 49 && buf[5] == 66)
			go_down(set);
		else
			fg_o_fd(set, buf[2], 0, set->col);
		free_buff(buf);
	}
	return (0);
}
