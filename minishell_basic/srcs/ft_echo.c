/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/11 13:38:24 by phbarrad         ###   ########.fr       */
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

int		ft_echo(t_set *set)
{
	int	i;
	int	n;
	int	w_print;

	i = 0;
	w_print = 0;
	n = 0;
	//printf("[Notre echo]\n");
	if (!set->arg[0])
	{
		ft_putchar_fd('\n', STDOUT);
		set->exit_val = 0;
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
		{
			set->exit_val = 0;
			return (0);
		}
	}
	while (set->arg[i])
	{
		ft_putstr_fd(set->arg[i], STDOUT);
		if (set->arg[i + 1])
			ft_putchar_fd(' ', STDOUT);
		w_print++;
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT);
	set->exit_val = 0;
	return (0);
}
