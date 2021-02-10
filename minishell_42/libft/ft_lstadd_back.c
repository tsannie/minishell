/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:03:58 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:06 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*tmp;

	if (alst != NULL)
		tmp = *alst;
	if (*alst == NULL && alst != NULL)
		*alst = new;
	else if (alst != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
