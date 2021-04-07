/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:32:10 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char			*double_slash(char *arg)
{
	int			i;
	char		*str;

	if (!arg)
		return (NULL);
	i = 0;
	str = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '\\' || arg[i] == '\"' || arg[i] == '$')
			str = add_letter(str, '\\');
		str = add_letter(str, arg[i]);
		i++;
	}
	return (str);
}

int				ft_hideenv(char *arg, t_set *set)
{
	int			i;
	int			act;
	char		*str;

	act = 0;
	i = 0;
	str = double_slash(arg);
	while (set->hide_envp[i] != NULL)
	{
		if (ncmpel(str, set->hide_envp[i]) == 0)
		{
			free(set->hide_envp[i]);
			set->hide_envp[i] = ft_strdup(str);
			act = 1;
		}
		i++;
	}
	if (act == 0)
	{
		set->hide_envp = addword(set->hide_envp, i + 1, str);
		set->hide_envp[i + 1] = NULL;
	}
	free(str);
	return (0);
}

int				ft_modenv(char *str, t_set *set)
{
	int			i;
	int			act;

	act = 0;
	i = 0;
	while (set->envp[i] != NULL)
	{
		if (ncmpel(str, set->envp[i]) == 0)
		{
			free(set->envp[i]);
			set->envp[i] = ft_strdup(str);
			act = 1;
		}
		i++;
	}
	if (act == 0)
	{
		set->envp = addword(set->envp, i + 1, str);
		set->envp[i + 1] = NULL;
	}
	return (0);
}
