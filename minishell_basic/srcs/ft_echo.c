/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:18:02 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/12 13:13:38 by phbarrad         ###   ########.fr       */
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

void		put_last_cmd(char *str)
{
	int i;

	i = 0;
	printf("[oui]ouio[uoi]\n");
	while (str[i])
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	ft_putstr_fd(str + i, STDOUT);
}

int		ft_echo(t_set *set)
{
	int	i;
	int	n;

	i = 0;
	n = 0;

	//printf("[Notre echo]\n");
	if (!set->arg[0])
	{
		ft_putchar_fd('\n', STDOUT);
		set->exit_val = 0;
		return (0);
	}
/* 	 	int x = -1;
	while (set->arg[++x])
		printf("arg[%s]\n", set->arg[x]);
  */
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
		//printf("[%s][%d]\n",set->arg[i], ft_strncmp(set->arg[i],"$_", ft_strlen(set->arg[i])));
		//if (ft_strncmp(set->arg[i],"$_", ft_strlen(set->arg[i])) == 0)
		//	put_last_cmd(set->arg[i]);
		//else
		//{
			ft_putstr_fd(set->arg[i], STDOUT);
			if (set->arg[i + 1])
				ft_putchar_fd(' ', STDOUT);
		//}
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT);
	set->exit_val = 0;
	return (0);
}
