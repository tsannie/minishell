/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_lib_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/10 12:39:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char			*ft_strdup_free_len(char *str, int len)
{
	int			i;
	char		*new;

	i = 0;
	if (!str || len <= 0)
	{
		ffree(str);
		return (ft_strdup(""));
	}
	if (!(new = malloc(sizeof(char) * (len))))
		return (NULL);
	while (i < len - 1)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	ffree(str);
	return (new);
}

char			*ft_strdup_free_pos(char *str, int len, int pos)
{
	int			i;
	char		*new;
	int			e;

	e = 0;
	i = 0;
	if (!str || len <= 0)
	{
		ffree(str);
		return (ft_strdup(""));
	}
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (pos == i)
			e++;
		new[i] = str[i + e];
		i++;
	}
	new[i] = '\0';
	ffree(str);
	return (new);
}

void			free_buff(char *buf)
{
	if (buf[0] != 0)
	{
		ft_bzero((void *)buf, BUF_SIZE);
		buf[0] = 0;
	}
}
