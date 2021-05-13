/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 10:33:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			aff_result(t_set *set, size_t len, size_t col)
{
	size_t		e;

	e = 0;
	while ((int)(len) > set->cur_pos)
	{
		if (((len) % col) == 0)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			while (++e < col)
				ft_putstr_fd(set->tt_right, STDERR);
		}
		else
			ft_putstr_fd(set->tt_left, STDERR);
		len--;
		e = 0;
	}
}

int				aff_modif_str(t_set *set, char *buf)
{
	size_t		len;
	size_t		col;

	col = set->col;
	set->str = ft_strjoin_free_len(set->str, buf, set->cur_pos - 12);
	len = ft_strlen(set->str) + 12;
	set->cur_pos++;
	if (set->cur_pos - 12 < (int)(ft_strlen(set->str)))
	{
		ft_putstr_fd(buf, STDERR);
		if (ft_strlen(buf) < 2)
			ft_putstr_fd(set->str + (set->cur_pos - 12), STDERR);
		if ((len % col) == 0)
		{
			ft_putstr_fd(" ", STDERR);
			ft_putstr_fd(set->tt_left, STDERR);
		}
		aff_result(set, len, col);
		return (1);
	}
	return (0);
}

void			cmd_free(t_set *set, char *buf)
{
	if (ft_strlen(set->str) == 0)
	{
		ft_putstr_fd("exit\n", STDERR);
		exit(0);
	}
	free_buff(buf);
}

void			all_ccmd(char *buf, t_set *set)
{
	int			oui;

	oui = 0;
	if (buf[0] == 127 && ft_strlen(buf) == 1)
	{
		if (set->cur_pos > 12)
			ft_dell(set);
		free_buff(buf);
	}
	else if (buf[0] == 9 && ft_strlen(buf) == 1)
		free_buff(buf);
	else if (ft_strlen(buf) >= 3 && buf[0] == 27)
		set_fle(set, buf);
	else if (ft_strlen(buf) == 1 && buf[0] == 4)
		cmd_free(set, buf);
	else if ((buf[0] == 22 && buf[1] == 0) || (buf[0] == 6 && buf[1] == 0) ||
	(buf[0] == 18 && buf[1] == 0))
		is_copy_cut(set, buf);
	else if (buf[0] != 10 && buf[0] != 127)
		oui = aff_modif_str(set, buf);
	if (oui == 0 && ft_strlen(buf) < 4)
		ft_putstr_fd(buf, STDERR);
}

void			eeddn(t_set *set)
{
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str)] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
	ffree(set->credir);
	set->credir = ft_strdup("");
	set->fl = 0;
}
