/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/09 15:46:26 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int is_noret(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int		disp_exit_val(t_set *set)
{
	int x;

	x = -1;
	while (set->str[++x])
	{
		if (ft_streql(set->str + x, "$?") == 1)
		{
			ft_putnbr_fd(set->exit_val, set->fd);
			ft_putchar_fd('\n', set->fd);
			set->exit_val = 0;
			return (1);
		}
	}
	return (0);
}

int		ft_echo(t_set *set)
{
	int	i;
	int	n;
	int	w_print;

	i = 0;
	w_print = 0;
	n = 0;
	if (!set->arg[0])
	{
		ft_putchar_fd('\n', set->fd);
		return (0);
	}
/* 	int x = -1;
	while (set->arg[++x])
		printf("[%s]\n", set->arg[x]);
	printf("str = [%s]\n", set->cmd);
	printf("word = [%s]\n", set->word_tmp);
	printf("str = [%s]\n", set->str);
 */
	//if (disp_exit_val(set) == 1)
	//	return (set->exit_val);
	while (is_noret(set->arg[i]) == 1)
	{
		i++;
		n = 1;
		if (!set->arg[i])
			return (0);
	}
	while (set->arg[i])
	{
		ft_putstr_fd(set->arg[i], set->fd);
		if (set->arg[i + 1])
			ft_putchar_fd(' ', set->fd);
		w_print++;
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', set->fd);
	set->exit_val = 0;
	return (0);
}
