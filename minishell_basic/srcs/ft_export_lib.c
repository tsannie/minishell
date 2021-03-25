/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:32:10 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 15:33:20 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char			*recup_new(char *str, int x)
{
	char		*nstr;
	int			j;

	j = 0;
	if (!(nstr = malloc(sizeof(char) * (ft_strlen(str) + 4))))
		return (0);
	while (j < x)
	{
		nstr[j] = str[j];
		j++;
	}
	nstr[j] = '\"';
	while (str[j])
	{
		nstr[j + 1] = str[j];
		j++;
	}
	nstr[j + 1] = '\"';
	nstr[j + 2] = '\0';
	return (nstr);
}

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
		set->hide_envp = addword(set->hide_envp, i + 1, str);		// not free (leak)
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
