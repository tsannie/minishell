/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:23 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/12 13:29:38 by phbarrad         ###   ########.fr       */
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
        if (ft_strcmpp(str + j, envp[i]) == 0){
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

int ft_unset(t_set *set, char **envp)
{
    int j;
	int i;

	i = 0;
	j = 0;
    while (set->str[j] != 't' && set->str[j])
        j++;
    while (set->str[j] == ' ' || set->str[j] == '\t')
        j++;
    while (envp[i] != NULL)
    {
        if (ft_strcmpp(set->str + j, envp[i]) == 0)
		{
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
}