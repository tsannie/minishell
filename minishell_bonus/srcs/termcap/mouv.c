/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int			history_prev(t_set *set)
{
	size_t len;

	len = ft_strlen(set->str);
	if (set->his_pos > 0 && set->history[set->his_pos - 1])
		set->his_pos--;
	else
		return (0);
	while (len-- > 0)
	{
		ft_putstr_fd(set->tt_left, STDERR);
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
	}
	ft_putstr_fd(set->history[set->his_pos], STDERR);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	return (0);
}

int			history_next(t_set *set)
{
	size_t len;

	len = ft_strlen(set->str);
	if (set->his_pos < set->inc_his && set->history[set->his_pos + 1])
		set->his_pos++;
	else
		return (0);
	while (len-- > 0)
	{
		ft_putstr_fd(set->tt_left, STDERR);
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
	}
	ft_putstr_fd(set->history[set->his_pos], STDERR);
	ffree(set->str);
	set->str = ft_strdup(set->history[set->his_pos]);
	return (0);
}
