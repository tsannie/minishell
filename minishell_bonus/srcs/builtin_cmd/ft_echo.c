/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int		is_noret(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int		no_arg(void)
{
	ft_putchar_fd('\n', STDOUT);
	return (0);
}

int		ft_echo(t_set *set)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!set->arg[0])
		return (no_arg());
	while (is_noret(set->arg[i]) == 1)
	{
		i++;
		n = 1;
		if (!set->arg[i])
			return (0);
	}
	while (set->arg[i])
	{
		ft_putstr_fd(set->arg[i], STDOUT);
		if (set->arg[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}
