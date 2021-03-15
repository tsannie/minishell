/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/15 09:21:57 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_env(t_set *set)
{
    int i;
	char *tmp;

	
	i = -1;
    while (set->envp[++i] != NULL)
    {
		if (ft_strncmp(set->envp[i], "?=", 2) != 0)
		{
			if (ft_strncmp(set->envp[i], "_=", 2) == 0)
			{
				ft_putstr_fd("_=monenv", STDOUT);//modif
				ft_putstr_fd(set->pwd + 4, STDOUT);
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
