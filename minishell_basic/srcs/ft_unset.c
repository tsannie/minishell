/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:23 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/17 08:59:06 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"
/*
int ft_unsetenv(char *str, char * envp[])
{
    int j;
	int i;

	i = 0;
	j = 0;
    while (str[j] != 't' && str[j])
        j++;
    while (str[j] == ' ' || str[j] == '\t')
        j++;
    while (envp[i] != NULL)
    {
        if (ft_streql(str + j, envp[i]) == 1){
            while (envp[i] != NULL)
            {
                envp[i] = envp[i+1];
                i++;
            }
            return (0);
        }
        i++;
    }
    return (0);
}*/

int ft_unset(t_set *set)
{
    int j;
	int i;

	i = 0;
	j = 0;
	while (set->arg[j])
	{
		while (set->envp[i] != NULL)
		{
			if (ft_streql(set->str, set->envp[i]) == 1)
			{
				while (set->envp[i] != NULL)
				{
					set->envp[i] = set->envp[i+1];
					i++;
				}
				return (0);
			}
			i++;
		}
		j++;
	}
    return (0);
}