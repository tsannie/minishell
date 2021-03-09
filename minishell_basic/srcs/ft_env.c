/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 10:17:21 by phbarrad         ###   ########.fr       */
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
		    ft_putstr_fd(set->envp[i], set->fd);
			ft_putchar_fd('\n', set->fd);
		}
	}
    return (0);
}
