/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 09:57:16 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/16 15:41:44 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		globalsize;
	int		i;
	int		e;

	if (!(s1) || !(s2))
		return (NULL);
	globalsize = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = malloc(sizeof(char) * globalsize + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	e = 0;
	while (s2[e])
	{
		res[i + e] = s2[e];
		e++;
	}
	res[globalsize] = '\0';
	return (res);
}
