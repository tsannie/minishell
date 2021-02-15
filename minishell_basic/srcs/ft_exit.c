/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:55:16 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/15 10:57:37 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minish.h"


void ft_eexit(t_set *set)
{
	if (ft_strcmpp(set->cmd, "exit") == 0)
		{
			if (set->arg[0] == NULL)
				exit(0);
			else
				exit(ft_atoi(set->arg[0]));
		}
}