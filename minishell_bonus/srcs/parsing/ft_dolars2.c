/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:36:59 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

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
	return (ft_ispair(n) == 1 ? 1 : 0);
}

char	*dolars_find(char *src)
{
	char	*res;
	int		i;

	i = 1;
	res = ft_strdup("");
	if (ft_isdigit(src[i]) == 1 || src[i] == '?')
	{
		res = add_letter(res, src[i]);
		return (res);
	}
	if (src[i] != '\"' && src[i] != '\'')
	{
		while (src[i] && (ft_isalnum(src[i]) == 1 || src[i] == '_'
			|| src[i] == '?'))
		{
			res = add_letter(res, src[i]);
			i++;
		}
	}
	return (res);
}

char	*before_equale(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
