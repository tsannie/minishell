/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:49:31 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/13 12:43:36 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_dbtab(char **tab)
{
	int i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
		tab = NULL;
	}
}
