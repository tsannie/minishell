/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/14 15:55:30 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		ft_echo(t_set *set)
{
	int	i;
	int	n;
	int	w_print;

	i = 0;
	w_print = 0;
	n = 0;
	if (!set->arg[0])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (ft_streql(set->arg[i], "-n") == 1)
	{
		i++;
		n = 1;
	}
	while (set->arg[i])
	{
		ft_putstr_fd(set->arg[i], 1);
		if (set->arg[i + 1])
			ft_putchar_fd(' ', 1);
		w_print++;
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
