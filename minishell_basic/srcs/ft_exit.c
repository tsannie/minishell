/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:55:16 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 13:50:03 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

unsigned long long		ft_atoill(const char *str)
{
	int i;
	unsigned long long result;

	i = 0;
	result = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}


int		ft_check_valid_exit(t_set *set)
{
	int i;
	long long max =  9223372036854775807;
	unsigned long long exit_val = ft_atoill(set->arg[0]);
	i = 0;
	//printf("[%s][%d][%zu]\n", set->arg[0],ft_atoi(set->arg[0]), ft_strlen(set->arg[0]));
	int len = 0;
	int len_disp = 0;
	if (set->arg[0][len_disp] == '-' || set->arg[0][len_disp] == '+')
			len_disp++;
	while (set->arg[0][len_disp] == '0')
			len_disp++;
	while (set->arg[0][len_disp])
	{
		len_disp++;
		len++;
	}
	//printf("len  = [%d]\n", len);
	//printf("[%llu]\n", exit_val);
	//printf("[%s][-9223372036854775808][%d]\n", set->arg[0],ft_streql(set->arg[0], "-9223372036854775808"));
	if (len > 19)
		return (1);
	if (exit_val > max && ft_streql(set->arg[0], "-9223372036854775808") != 1)
	{
	 //	printf("oui\n");
		return (1);
	}
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

void	ft_eexit(t_set *set)
{
	int len;

	len = 0;
    if (ft_streql(set->cmd, "exit") != 1)
    {
        ft_putstr_not_found(set->cmd, set);
		exit(set->exit_val);
    }
	while (set->arg[len])
		len++;
	if (set->arg[0] == NULL)
		exit(0);
	else if (ft_check_valid_exit(set) == 1)
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
	if (len > 1)
	{
		//ft_putstr_fd(set->cmd, STDERR);
	//	ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(set->cmd, STDERR);
		ft_putstr_fd(": too many arguments\n", STDERR);
		set->exit_val = 1;
		//exit (1); jsp
	}
	else
	{
		//ft_putstr_fd(set->cmd, STDERR);
		//ft_putstr_fd("\n", STDERR);
		exit(ft_atoi(set->arg[0]));
	}
}