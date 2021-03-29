/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:28:38 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 15:32:22 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int					ft_strcmpss(char *s1, char *s2)
{
	int				i;

	i = 0;
	if (ft_strlen(s1) - 1 != ft_strlen(s2))
		return (1);
	while (s1[i] == s2[i] && s1[i] && s1[i + 1] != '/')
		i++;
	return (s1[i] - s2[i]);
}

int					ft_strcmpsl(char *s1, char *s2)
{
	int				i;
	int				len;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	if (s1[len - 1] == '/')
		len--;
	while (s1[i] == s2[i] && s1[i] && i < len)
		i++;
	return (s1[i] - s2[i]);
}
