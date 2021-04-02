/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/01 16:51:23 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

void					errdsp(t_set *set)
{
	ft_putstr_fd(set->cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(set->arg[0], STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	free_all(set, set->exit_val);
	exit(255);
}

void					retarg(t_set *set)
{
	int					ret;

	ft_putstr_fd(set->cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	ret = ft_atoi(set->arg[0]);
	free_all(set, set->exit_val);
	exit(ret);
}

void					ft_eexit(t_set *set)
{
	int					len;
	int					ret;

	ret = 0;
	len = 0;
	while (set->arg[len])
		len++;
	if (set->arg[0] == NULL)
	{
		ret = set->exit_val;
		free_all(set, set->exit_val);
		exit(ret);
	}
	else if (ft_check_valid_exit(set) == 1)
		errdsp(set);
	if (len > 1)
	{
		ft_putstr_fd(set->cmd, STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(set->cmd, STDERR);
		ft_putstr_fd(": too many arguments\n", STDERR);
		set->exit_val = 1;
		set->ex_er = 1;
	}
	else
		retarg(set);
}
