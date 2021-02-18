/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solo_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:36:45 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/18 15:46:33 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void		ft_sort_dbtab(t_set *set)
{
	int		i;
	char	*temp;

/* 	i = 0;
	//set->hide_envp[12 + 1] = malloc(sizeof(char) * 1);
    //set->hide_envp[12 + 1] = NULL;
	while (set->hide_envp[i] != NULL)
	{
		printf("{%s}\n", set->hide_envp[i]);
		i++;
	} */
	i = 0;
	while (set->hide_envp[i + 1] != NULL)
	{
		//printf("[%d][%s][%s]\n", i,set->hide_envp[i], set->hide_envp[i + 1]);
		if (ft_strcmp(set->hide_envp[i], set->hide_envp[i + 1]) > 0)
		{
			temp = set->hide_envp[i];
			set->hide_envp[i] = set->hide_envp[i + 1];
			set->hide_envp[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

int ft_disp_export(t_set *set)
{
    int i;
	int x;
	int egl;
	char *var;

	egl = 0;
	x = 0;
	i = 0;
	ft_sort_dbtab(set);
    while (set->hide_envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		x = 0;
		while (set->hide_envp[i][x] != '=' && set->hide_envp[i])
		{
			ft_putchar_fd(set->hide_envp[i][x], 1);
			x++;
		}
		if (set->hide_envp[i][x])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(set->hide_envp[i], 1);
			ft_putstr_fd("\"\n", 1);
		}

		i++;
	}
    //printf("declare -x %s\n", set->hide_envp[i]);
    return (0);
}
