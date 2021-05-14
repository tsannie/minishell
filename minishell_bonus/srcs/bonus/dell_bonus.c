/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dell_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/10 12:55:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			revenir_pos(t_set *set, size_t len)
{
	int			cursor;
	int			e;
	int			x;

	x = 0;
	e = 0;
	cursor = set->cur_pos - 1;
	while ((int)(len) > cursor)
	{
		if (((len) % set->col) == 0 && x != 0 && (int)(len) >= set->col)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			while (e++ < set->col)
				ft_putstr_fd(set->tt_right, STDERR);
		}
		else
			ft_putstr_fd(set->tt_left, STDERR);
		len--;
		e = 0;
		x++;
	}
	if (((int)(ft_strlen(set->str) + 12) == set->col) &&
	((int)((ft_strlen(set->str) + 13)) != set->cur_pos))
		ft_putstr_fd(set->tt_right, STDERR);
}

void			disp_rest_str(t_set *set, size_t col)
{
	size_t		e;

	e = 0;
	ft_putstr_fd(set->str + (set->cur_pos - 13), STDERR);
	if (set->cur_pos != (int)(ft_strlen(set->str) + 13))
	{
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
		if (((ft_strlen(set->str) + 12) % (col)) == 0)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			while (++e < col)
				ft_putstr_fd(set->tt_right, STDERR);
		}
		revenir_pos(set, ft_strlen(set->str) + 12);
		if ((((ft_strlen(set->str) + 12) % (col)) == 0) &&
		(ft_strlen(set->str) + 12 > col))
			ft_putstr_fd(set->tt_right, STDERR);
		if (((ft_strlen(set->str) + 13) % (col)) == 0)
			ft_putstr_fd(set->tt_right, STDERR);
	}
	else
		revenir_pos(set, ft_strlen(set->str) + 12);
}

void			aff_end_col(t_set *set, size_t len)
{
	size_t		e;

	e = 0;
	ft_putstr_fd(set->tt_up, STDERR);
	while (++e < len + 12)
		ft_putstr_fd(set->tt_right, STDERR);
	ft_putstr_fd("  ", STDERR);
	e = 0;
	ft_putstr_fd(set->tt_up, STDERR);
	while (++e < len + 12)
		ft_putstr_fd(set->tt_right, STDERR);
	ft_putstr_fd(set->tt_right, STDERR);
}

int				ft_dell(t_set *set)
{
	size_t		len;
	size_t		col;

	col = set->col;
	len = ft_strlen(set->str);
	set->str = ft_strdup_free_pos(set->str, len, set->cur_pos - 13);
	set->dell_len = getdellen(set->cur_pos, col);
	if (set->cur_pos - 12 > 0)
	{
		if ((set->cur_pos % col) == 0)
			aff_end_col(set, len);
		else
			aff_dell(set);
		disp_rest_str(set, col);
	}
	set->cur_pos--;
	return (0);
}
