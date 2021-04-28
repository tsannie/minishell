/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solo_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:36:45 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int			ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void		ft_sort_dbtab(t_set *set)
{
	int		i;
	char	*temp;

	i = 0;
	while (set->hide_envp[i + 1] != NULL)
	{
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

void		put_hid(t_set *set, int i, int x)
{
	ft_putstr_fd("=\"", STDOUT);
	ft_putstr_fd(&set->hide_envp[i][x + 1], STDOUT);
	ft_putstr_fd("\"", STDOUT);
}

int			ft_disp_export(t_set *set)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (set->hide_envp[i])
	{
		if (ft_strncmp(set->hide_envp[i], "?=", 2) != 0 &&
		ft_strncmp(set->hide_envp[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT);
			x = 0;
			while (set->hide_envp[i][x] != '=' && set->hide_envp[i][x])
			{
				ft_putchar_fd(set->hide_envp[i][x], STDOUT);
				x++;
			}
			if (set->hide_envp[i][x])
				put_hid(set, i, x);
			ft_putchar_fd('\n', STDOUT);
		}
		i++;
	}
	return (0);
}
