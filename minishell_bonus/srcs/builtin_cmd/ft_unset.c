/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:23 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int					ncmpel(char *s1, char *s2)
{
	int				i;

	i = 0;
	while ((s2[i] || s1[i]) && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int					checkenvp_un(char *str)
{
	int				i;
	int				avn;

	i = 0;
	avn = 0;
	if (ft_strlen(str) == 0)
		return (1);
	if (str[i] == '=')
		return (1);
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 59 && avn == 0)
			return (1);
		if (((str[i] < 48) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 123)
		|| (str[i] >= 91 && str[i] <= 96)) && (str[i] != '_'))
			return (1);
		else
			avn = 1;
		i++;
	}
	return (0);
}

char				**ft_unsetenv(t_set *set, char *str)
{
	int				i;
	int				e;
	char			**res;

	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	i = 0;
	e = 0;
	while (set->envp[i])
	{
		if (ncmpel(str, set->envp[i]) != 0)
		{
			e++;
			res = addword(res, e, set->envp[i]);
		}
		i++;
	}
	ft_free_dbtab(set->envp);
	return (res);
}

char				**ft_unsethideenv(t_set *set, char *str)
{
	int				i;
	int				e;
	char			**res;

	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	i = 0;
	e = 0;
	while (set->hide_envp[i])
	{
		if (ncmpel(str, set->hide_envp[i]) != 0)
		{
			e++;
			res = addword(res, e, set->hide_envp[i]);
		}
		i++;
	}
	ft_free_dbtab(set->hide_envp);
	return (res);
}

int					ft_unset(t_set *set)
{
	int				j;

	j = 0;
	while (set->arg[j])
	{
		if (checkenvp_un(set->arg[j]) == 1)
		{
			ft_putstr_fd("minishell: unset: `", STDERR);
			ft_putstr_fd(set->arg[j], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
			set->exit_val = 1;
			set->bleu = 1;
		}
		else
		{
			set->hide_envp = ft_unsethideenv(set, set->arg[j]);
			set->envp = ft_unsetenv(set, set->arg[j]);
		}
		j++;
	}
	return (0);
}
