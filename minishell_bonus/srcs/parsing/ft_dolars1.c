/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 08:05:14 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char	*before_equal(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!(res = malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '=';
	res[i + 1] = '\0';
	return (res);
}

char	*change_dol(char *dol, t_set *set)
{
	int		i;
	int		e;
	char	*res;
	char	*var;

	i = 0;
	e = 0;
	dol = add_letter(dol, '=');
	while (set->hide_envp[i] && e == 0)
	{
		var = before_equal(set->hide_envp[i]);
		if (ft_streql(var, dol) == 1)
		{
			while (set->hide_envp[i][e] != '=' && set->hide_envp[i][e])
				e++;
			if (set->hide_envp[i][e])
				res = ft_strdup(&set->hide_envp[i][e + 1]);
			else
				res = ft_strdup("");
		}
		free(var);
		i++;
	}
	free(dol);
	return ((e == 0) ? ft_strdup("") : res);
}

char	*place_dol(char *src, char *dol, t_set *set)
{
	char	*res;
	int		i;
	int		e;

	res = ft_strdup("");
	i = 0;
	e = 0;
	while (i < set->dol_found)
	{
		res = add_letter(res, src[i]);
		i++;
	}
	while (dol[e])
	{
		res = add_letter(res, dol[e]);
		e++;
	}
	i += set->l_dol + 1;
	while (src[i])
	{
		res = add_letter(res, src[i]);
		i++;
	}
	free(src);
	return (res);
}

int		simplequot_dol(int i, char *res)
{
	i++;
	while (res[i] && res[i] != '\'')
		i++;
	return (i);
}

char	*search_dolars(char *src, t_set *set)
{
	int		i;
	char	*dol;
	char	*res;

	i = 0;
	res = ft_strdup(src);
	while (res[i])
	{
		if (res[i] == '\'' && antislash_pair(res, i) == 1)
			i = simplequot_dol(i, res);
		else if (res[i] == '$' && (res[i + 1] == '\''
		|| ft_isalnum(res[i + 1]) == 1 || res[i + 1] == '_'
		|| res[i + 1] == '?') && antislash_pair(res, i) == 1)
		{
			set->dol_found = i;
			dol = dolars_find(&res[i]);
			set->l_dol = ft_strlen(dol);
			dol = change_dol(dol, set);
			res = place_dol(res, dol, set);
			free(dol);
			i = -1;
		}
		i++;
	}
	return (res);
}
