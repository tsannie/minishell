/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/06 16:23:48 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"


int			move_left(t_set *set)
{
/* 	if (!(set->input) || !(set->curs_pos))
		return (-1);
	replace_cursor(set, 0, 1);
	set->curs_pos = set->curs_pos->prev; */
	return (0);
}

int			move_right(t_set *set)
{
/* 	if (!(set->input) || (set->curs_pos && !(set->curs_pos->next)))
		return (-1);
	if (!(set->curs_pos))
		set->curs_pos = set->input;
	else
		set->curs_pos = set->curs_pos->next;
	replace_cursor(set, 0, 0); */
	return (0);
}

int			history_prev(t_set *set)
{
    if (set->his_pos > 0)
        set->his_pos--;
    printf("\n\n\n [%s][%d] \n\n\n",set->history[set->his_pos], set->his_pos);
    //tputs(tgetstr("sc", NULL), set->history[set->his_pos], &putchar);
	//tputs(tgetstr("cl", NULL),set->history[set->his_pos], &putchar);
    

/* 	t_input		*tmp;

	if ((!set->hist) || (!set->hist->prev && !set->hist_end))
		return (-1);
	if (set->hist_end && set->input)
		store_input_buf(set->input, set->input_len, &(set->input_buf));
	if (set->hist_end)
		set->hist_end = 0;
	else
		set->hist = set->hist->prev;
	if (set->input)
		clear_input(set);
	tmp = set->hist->input;
	while (tmp)
	{
		store_input(set, tmp->c);
		tmp = tmp->next;
	}
	print_input(set, set->input, set->p_len); */
	return (0);
}

int			history_next(t_set *set)
{
    if (set->his_pos < set->inc_his)
        set->his_pos++;
    //printf("\n\n\n [%s][%d] \n\n\n",set->history[set->his_pos], set->his_pos);
   // tputs(tgetstr("sc", NULL), set->history[set->his_pos], &putchar);
	//tputs(tgetstr("cl", NULL),set->history[set->his_pos], &putchar);
/* 	t_input	*tmp;

	if ((!set->hist) || (!set->hist->next && set->hist_end))
		return (-1);
	if (set->input)
		clear_input(set);
	if (!(set->hist->next))
		print_input_buf(set);
	else if (set->hist->next)
	{
		set->hist = set->hist->next;
		tmp = set->hist->input;
		while (tmp)
		{
			store_input(set, tmp->c);
			tmp = tmp->next;
		}
		print_input(set, set->input, set->p_len);
	} */
	return (0);
}
