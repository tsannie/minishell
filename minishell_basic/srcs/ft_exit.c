/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:55:16 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/15 13:38:15 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		ft_check_valid_exit(t_set *set)
{
	int i;

	i = 0;
	while (set->arg[0][i])
	{
		if (set->arg[0][i] == '-' || set->arg[0][i] == '+')
			i++;
		if (!(set->arg[0][i] <= '9'  && set->arg[0][i] >= '0') &&
		!((set->arg[0][i] == ' ' || set->arg[0][i] == '\t' ||
		set->arg[0][i] == '\v' || set->arg[0][i] == '\r' ||
		set->arg[0][i] == '\f' || set->arg[0][i] == '\n')))
			return (1);
		i++;
	}
	return (0);
}

void	ft_eexit(t_set *set)
{
	int len;

	len = 0;
	if (ft_strcmpp(set->cmd, "exit") == 0)
	{
		while (set->arg[len])
			len++;
		if (set->arg[0] == NULL)
			exit(0);
		else if (ft_check_valid_exit(set) == 1)
		{
			printf("minishell: %s: %s: numeric argument required\n", set->cmd, set->arg[0]);
			exit(255);
		}
		if (len > 1)
		{
			printf("minishell: %s: too many arguments\n", set->cmd);
			exit (1);
		}
		else
			exit(ft_atoi(set->arg[0]));
	}
}