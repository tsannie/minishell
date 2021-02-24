/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 08:05:14 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/24 23:02:53 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		antislash_pair(char *src, int i)
{
	int n;

	n = 1;
	i--;
	while (src[i] && src[i] == '\\')
	{
		i--;
		n++;
	}
	return (ft_ispair(n) == 1 ? 1 : 0);
}

char	*dolars_find(char *src, t_set *set, int i)
{
	char	*dol;

	dol = ft_strdup("");
	i++;
	if (src[i] == '\'' || src[i] == '\"')
	{
		//quote();
	}
	else
	{
		while (src[i] && (ft_isalnum(src[i]) == 1 || src[i] == '_')) // ATTENTION Y'EN A D'AUTRES !
		{
			dol = add_letter(dol, src[i]);
			i++;
		}
	}
	return (dol);
}

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
		//printf("\n\nvar = %s\n\n", var);
		if (ft_streql(var, dol) == 1)
		{
			while(set->hide_envp[i][e] != '=')
				e++;
			res = ft_strdup(&set->hide_envp[i][e + 1]);
		}
		free(var);
		i++;
	}
	free(dol);
	if (e == 0)
		res = ft_strdup("");
	return (res);
}

char	*place_dol(char *src, char *dol, t_set *set)
{
	char	*res;
	int		i;
	int		e;

	res = ft_strdup("");
	i = 0;
	e = 0;
	//printf("src = {%s}\n", src);
	while (src[i])
	{
		if (src[i] == '\\' && src[i + 1] == '$')
		{
			if (antislash_pair(src, i) == 0)
			{
				res = add_letter(res, src[i]);
				res = add_letter(res, src[i + 1]);
				i = i + 2;
			}
		}
		else if (src[i] == '$' && e == 0)
		{
			if (src[i + 1] == '\'' || src[i + 1] == '\"')
				i = i + 2;
			while (dol[e])
			{
				res = add_letter(res, dol[e]);
				e++;
			}
			//printf("\nl_dol = %d\n", set->l_dol);
			i = set->l_dol + i + 1;
			//printf("\nsrc[i] = %d\n", set->l_dol);
			e++;
		}
		else
		{
			res = add_letter(res, src[i]);
			//printf("\n\nRES = {%s}\n\n", res);
			i++;
		}
	}
	//printf("\n\nRES = {%s}\n\n", res);
	return (res);
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
		if (res[i] == '\\' && res[i + 1] == '$')
		{
			if (antislash_pair(res, i) == 0)
				i = i + 2;
		}
		if (res[i] == '$')
		{
			dol = dolars_find(res, set, i);
			//printf("\nICI dol = %s\n", dol);
			set->l_dol = ft_strlen(dol);
			//printf("\n\ndol_b = {%s}\n\n", dol);
			dol = change_dol(dol, set);
			//printf("\n\ndol_a = {%s}\n\n", dol);
			res = place_dol(res, dol, set);
			//printf("RES = |%s|\n", res);
			free(dol);
			i = -1;
		}
		i++;
	}
	return (res);
}
