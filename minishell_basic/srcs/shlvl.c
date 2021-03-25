/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:41:18 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 16:33:26 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void						init_shlvl(unsigned long long val,
t_set *set, int value)
{
	long long				max;

	max = 9223372036854775807;
	if (val > (unsigned long long)max)
		value = 0;
	if (value > 2147483646)
		value = 0;
	else if (value < 0)
		value = 0;
	else if (value == 0)
		value = 1;
	else if (value > 200000 + 1)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR);
		ft_putnbr_fd(value + 1, STDERR);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR);
		value = 1;
	}
	else
		value += 1;
	set->shlvl = ft_itoa(value);	
}

int							check_shlvl(t_set *set, char **envp)
{
	int						i;
	int						value;
	unsigned long long		val;

	val = 0;
	value = 0;
	set->shlvl = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			val = ft_atoill(envp[i] + 6);
			value = ft_atoi(envp[i] + 6);
		}
	}
	init_shlvl(val, set, value);
	return (0);
}
