/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_copy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/12 15:22:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int				ft_strlen_space(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void			go_copy(t_set *set)
{
	char		*new;
	int			len;
	int			i;
	int			e;

	e = 0;
	i = 0;
	len = 0;
	while (set->str[i] && i < (set->cur_pos - 12))
		i++;
	while (set->str[i] != ' ' && i >= 0)
		i--;
	i++;
	len = ft_strlen_space(set->str + i);
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return ;
	while (set->str[i + e] != ' ' && set->str[i + e])
	{
		new[e] = set->str[i + e];
		e++;
	}
	new[e] = 0;
	ffree(set->edit_copy);
	set->edit_copy = new;
}

void			go_cut(t_set *set)
{
	go_copy(set);
	while (set->str[set->cur_pos - 12] != ' ' && set->str[set->cur_pos - 12])
		fg_o_fd(set, 70);
	if (set->cur_pos - 12 > 0)
		ft_dell(set);
	while (set->str[set->cur_pos - 12 - 1] != ' ' && set->cur_pos - 12 - 1 >= 0)
		ft_dell(set);
}

char			*go_paste(t_set *set)
{
	int			i;
	char		*new;
	int			e;

	e = 0;
	i = 0;
	if (!(new = malloc(sizeof(char) *
	(ft_strlen(set->str) + ft_strlen(set->edit_copy) + 1))))
		return (NULL);
	while (i < (set->cur_pos - 12))
	{
		new[i] = set->str[i];
		i++;
	}
	while (set->edit_copy[e])
	{
		new[i] = set->edit_copy[e];
		e++;
		i++;
	}
	while (set->str[i - e])
	{
		new[i] = set->str[i - e];
		i++;
	}
	new[i] = '\0';
	ffree(set->str);
	return (new);
}

void			is_copy_cut(t_set *set, char *buf)
{
	int pos;


	if (buf[0] == 22 && buf[1] == 0)
	{
		go_copy(set);
		free_buff(buf);
	}
	else if (buf[0] == 6 && buf[1] == 0)
	{
		go_cut(set);
		free_buff(buf);
	}
	else if (buf[0] == 18 && buf[1] == 0 && set->edit_copy != NULL)
	{
		pos = set->cur_pos;
		set->str = go_paste(set);
		while (set->cur_pos - 12 > 0)
			fg_o_fd(set, 72);
		ft_putstr_fd(set->str, STDERR);
		set->cur_pos = ft_strlen(set->str) + 12;
		while (set->cur_pos > pos)
			fg_o_fd(set, 72);
		free_buff(buf);
	}
	else if (buf[0] == 18 && buf[1] == 0 && set->edit_copy == NULL)
		free_buff(buf);

}
