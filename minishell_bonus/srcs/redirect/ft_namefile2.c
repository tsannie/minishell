/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_namefile2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:08:54 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char	*dolars_redirect(char *src, t_set *set)
{
	char	*res;

	set->y++;
	res = ft_strdup("");
	if (ft_isdigit(src[set->y]) == 1 || src[set->y] == '?')
	{
		res = add_letter(res, src[set->y]);
		set->y++;
		return (res);
	}
	if (src[set->y] != '\"' && src[set->y] != '\'')
	{
		while (src[set->y] && (ft_isalnum(src[set->y]) == 1
		|| src[set->y] == '_' || src[set->y] == '?'))
		{
			res = add_letter(res, src[set->y]);
			set->y++;
		}
	}
	return (res);
}

void	refresh_amb(char *dol, t_set *set)
{
	char	*res;

	res = ft_strjoin("$", dol);
	set->dol_amb = ft_strjoin_free(set->dol_amb, res);
	free(res);
}

char	*get_newcmd(char *src, t_set *set, int i)
{
	char	*res;
	int		e;

	res = ft_strdup("");
	e = 0;
	while (e != i)
	{
		res = add_letter(res, src[e]);
		e++;
	}
	e = set->y;
	while (src[e])
	{
		res = add_letter(res, src[e]);
		e++;
	}
	free(src);
	return (res);
}
