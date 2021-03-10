/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/10 11:16:24 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_env(t_set *set)
{
    int i;

	i = -1;
    while (set->envp[++i] != NULL)
    {
		if (ft_strncmp(set->envp[i], "?=", 2) != 0)
		{
		    ft_putstr_fd(set->envp[i], STDOUT);
			ft_putchar_fd('\n', STDOUT);
		}
	}
    return (0);
}
