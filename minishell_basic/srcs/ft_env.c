/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/08 09:55:08 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_env(t_set *set)
{
    int i;
	
	i = -1;
    while (set->envp[++i] != NULL)
        ft_putstr_fd(set->envp[i], set->fd);
    return (0);
}
