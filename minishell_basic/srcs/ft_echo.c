/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/11 08:37:50 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		quote_present(char *str, char a)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

void	all_print(int *i, t_set *set, char a)
{
	(*i)++;
	while (set->str[(*i)] != a)
	{
		ft_putchar_fd(set->str[(*i)], 1);
		(*i)++;
	}
	(*i)++;
}

int		ft_echo(t_set *set)
{
	int	i;
	int	word;
	int	op_n;

	i = 5;
	word = 0;
	op_n = 0;
	while (set->str[i])
	{
		while (ft_iswhite(set->str[i]) == 1 && set->str[i])
			i++;
		if (set->str[i])
		{
			if (word != 0)
				ft_putchar_fd(' ', 1);
			if (set->str[i] == '-' && set->str[i + 1] == 'n'
				&& ft_iswhite(set->str[i + 2]) == 1 && word == 0)
			{
				op_n = 1;
				i = i + 2;
			}
			else
				word++;
		}
		while (ft_iswhite(set->str[i]) == 0 && set->str[i])
		{
			if (set->str[i] == '\'' && quote_present(&set->str[i], '\'') == 1)
				all_print(&i, set, '\'');
			else if (set->str[i] == '\"' && quote_present(&set->str[i], '\"') == 1)
				all_print(&i, set, '\"');
			else
			{
				ft_putchar_fd(set->str[i], 1);
				i++;
			}
		}
	}
	if (op_n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
