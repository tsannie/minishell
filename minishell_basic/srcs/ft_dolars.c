/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 08:05:14 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/09 10:17:43 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		antislash_pair(char *src, int i)
{
	int n;

	n = 0;
	if (src[i - 1] == '\\')
	{
		i--;
		while (src[i] && src[i] == '\\')
		{
			i--;
			n++;
		}
	}
	//printf("n = %d\n", n);
	return (ft_ispair(n) == 1 ? 1 : 0);
}

char	*dolars_find(char *src, t_set *set)
{
	char	*res;
	int		err;
	int		i;

	i = 1;
	res = ft_strdup("");
	err = 0;
	if (src[i] != '\"' &&  src[i] != '\'')
	{
		while (src[i] && (ft_isalnum(src[i]) == 1 || src[i] == '_' || src[i] == '?')) // ATTENTION Y'EN A D'AUTRES !
		{
			res = add_letter(res, src[i]);
			i++;
		}
	}
	return (res);
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
		if (src[i] == '\'')
		{
			res = add_letter(res, src[i]);
			i++;
			while (src[i] && src[i] != '\'')
			{
				res = add_letter(res, src[i]);
				i++;
			}
			res = add_letter(res, src[i]);
			i++;
		}
		else if (src[i] == '\\' && src[i + 1] == '$')
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
			//res = add_letter(res, '\"');
			if (src[i + 1] == '\'' || src[i + 1] == '\"')
				i = i + 2;
			while (dol[e])
			{
				res = add_letter(res, dol[e]);
				e++;
			}
			//res = add_letter(res, '\"');
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
		//printf("char = {%c}\n", res[i]);
		if (res[i] == '\'' && antislash_pair(res, i) == 1)
		{
			//ft_putstr_fd("\n\nNEXT :{",1);
			i++;
			while (res[i] && res[i] != '\'')
			{
				//ft_putchar_fd(res[i], 1);
				i++;
			}
			//ft_putstr_fd("}",1);
			//printf(" | res[i] = %c | i = %d\n", res[i], i);
		}
		else if (res[i] == '$' && (res[i + 1] == '\'' || res[i + 1] == '\"' || ft_isalnum(res[i + 1]) == 1 || res[i + 1] == '_' || res[i + 1] == '?') && antislash_pair(res, i) == 1)
		{
			dol = dolars_find(&res[i], set);
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
	free(src);
	return (res);
}
