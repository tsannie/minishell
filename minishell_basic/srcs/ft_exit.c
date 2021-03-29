/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:55:16 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 15:07:11 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int						iswt(t_set *set, int i)
{
	if (set->arg[0][i] == '-' || set->arg[0][i] == '+')
		i++;
	while (ft_iswhite(set->arg[0][i]) == 1)
		i++;
	while (set->arg[0][i])
	{
		if (!(set->arg[0][i] <= '9' && set->arg[0][i] >= '0') &&
		!((set->arg[0][i] == ' ' || set->arg[0][i] == '\t')))
			return (1);
		i++;
	}
	return (0);
}

int						set_len_disp(t_set *set)
{
	int len_disp;

	len_disp = 0;
	if (set->arg[0][len_disp] == '-' || set->arg[0][len_disp] == '+')
		len_disp++;
	while (set->arg[0][len_disp] == '0')
		len_disp++;
	return (len_disp);
}

int						ft_check_valid_exit(t_set *set)
{
	int					i;
	long long			max;
	unsigned long long	exit_val;
	int					len;
	int					len_disp;

	max = 9223372036854775807;
	exit_val = ft_atoill(set->arg[0]);
	len = 0;
	len_disp = set_len_disp(set);
	i = 0;
	while (set->arg[0][len_disp])
	{
		len_disp++;
		len++;
	}
	if (len > 19)
		return (1);
	if (exit_val > (unsigned long long)max &&
	ft_streql(set->arg[0], "-9223372036854775808") != 1)
		return (1);
	if (iswt(set, i) == 1)
		return (1);
	return (0);
}

void					errdsp(t_set *set)
{
	//ft_putstr_fd(set->cmd, STDERR);
	//ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(set->arg[0], STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	exit(255);
}

void					ft_eexit(t_set *set)
{
	int					len;

	len = 0;
	while (set->arg[len])
		len++;
	if (set->arg[0] == NULL)
		exit(set->exit_val);
	else if (ft_check_valid_exit(set) == 1)
		errdsp(set);
	if (len > 1)
	{
		//ft_putstr_fd(set->cmd, STDERR);
	//	ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(set->cmd, STDERR);
		ft_putstr_fd(": too many arguments\n", STDERR);
		set->exit_val = 1;
		set->ex_er = 1;
	}
	else
	{
		//ft_putstr_fd(set->cmd, STDERR);
		//ft_putstr_fd("\n", STDERR);
		exit(ft_atoi(set->arg[0]));
	}
}
