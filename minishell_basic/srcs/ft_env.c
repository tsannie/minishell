/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/11 12:32:38 by phbarrad         ###   ########.fr       */
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
		printf("[%s][%d]\n", set->envp[i], ft_strncmp(set->envp[i], "?=", 2));
	}
    return (0);
}
