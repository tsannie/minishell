/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 08:05:14 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/17 08:49:58 by tsannie          ###   ########.fr       */
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

void	dolars_find(char *src, int i, t_set *set)
{

}

char	*search_dolars(char *src, t_set *set)
{
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\\' && src[i + 1] == '$')
		{
			if (antislash_pair == 0)
				i = i + 2;
		}
		if (src[i] == '$')
			dolars_find():
		i++;
	}
}