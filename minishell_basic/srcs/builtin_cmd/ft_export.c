/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:27:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int				check_plus(char *str)
{
	int			i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

int				checkenvp(char *str)
{
	int			i;
	int			avn;

	i = 0;
	avn = 0;
	if (ft_strlen(str) == 0)
		return (1);
	if (str[i] == '=' || str[ft_strlen(str) - 1] == '+')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] >= 48 && str[i] <= 59 && avn == 0)
			return (1);
		if (((str[i] < 48 && str[i] != 43) || (str[i] >= 58 && str[i] <= 64) ||
		(str[i] >= 123) || (str[i] >= 91 && str[i] <= 96)) && (str[i] != '_'))
			return (1);
		else
			avn = 1;
		i++;
	}
	i = check_plus(str);
	return (i);
}

int				ret_egl(t_set *set, int i)
{
	int			egl;
	int			j;

	j = -1;
	egl = 0;
	while (set->arg[i][++j])
	{
		if (ft_strncmp(set->arg[i] + j, "+=", 2) == 0 && egl == 0)
			egl = 2;
		else if (set->arg[i][j] == '=' && egl == 0)
			egl = 1;
	}
	return (egl);
}

void			disp_eenv(t_set *set, int i)
{
	int egl;

	egl = ret_egl(set, i);
	if (egl == 2)
	{
		ft_eghide(set->arg[i], set);
		ft_egenv(set->arg[i], set);
	}
	else if (egl == 1)
	{
		ft_hideenv(set->arg[i], set);
		ft_modenv(set->arg[i], set);
	}
	else
		ft_hideenv(set->arg[i], set);
}

int				ft_export(t_set *set)
{
	int			i;

	i = -1;
	if (set->arg[0] == NULL)
		ft_disp_export(set);
	else
	{
		while (set->arg[++i])
		{
			if (checkenvp(set->arg[i]) == 1)
			{
				ft_putstr_fd("minishell: export: `", STDERR);
				ft_putstr_fd(set->arg[i], STDERR);
				ft_putstr_fd("': not a valid identifier\n", STDERR);
				set->exit_val = 1;
				set->bleu = 1;
			}
			else
				disp_eenv(set, i);
		}
	}
	ft_sort_dbtab(set);
	return (0);
}
