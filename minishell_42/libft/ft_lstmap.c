/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:07:50 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r_list;
	t_list	*r_point;

	if (!lst || !f)
		return (NULL);
	r_list = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		r_point = ft_lstnew(f(lst->content));
		if (!(r_point))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&r_list, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&r_list, r_point);
	}
	return (r_list);
}
