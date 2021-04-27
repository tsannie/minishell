/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int			ft_env(t_set *set)
{
	int		i;

	i = -1;
	while (set->envp[++i] != NULL)
	{
		if (ft_strncmp(set->envp[i], "?=", 2) != 0)
		{
			if (ft_strncmp(set->envp[i], "_=", 2) == 0)
			{
				ft_putstr_fd("_=", STDOUT);
				ft_putstr_fd(set->path, STDOUT);
				ft_putstr_fd("/", STDOUT);
				ft_putstr_fd(set->envp[i] + 2, STDOUT);
				ft_putchar_fd('\n', STDOUT);
			}
			else
			{
				ft_putstr_fd(set->envp[i], STDOUT);
				ft_putchar_fd('\n', STDOUT);
			}
		}
	}
	return (0);
}
