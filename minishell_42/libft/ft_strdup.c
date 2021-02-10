/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:25:03 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*str;
	int		i;

	i = -1;
	len = 0;
	while (s1[len])
		len++;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++i < len)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
