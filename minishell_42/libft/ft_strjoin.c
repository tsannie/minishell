/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:16:04 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*tab;
	unsigned int	len;
	unsigned int	i;

	i = -1;
	len = -1;
	if (!s1 || !s2)
		return (NULL);
	if (!(tab = malloc(sizeof(char) *
	(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	while (s2[++len])
		tab[i + len] = s2[len];
	tab[i + len] = '\0';
	return (tab);
}
