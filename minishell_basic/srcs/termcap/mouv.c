/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:32:30 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/23 17:46:52 by phbarrad         ###   ########.fr       */
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
	size_t len;
	
	len = ft_strlen(set->str);
    if (set->his_pos > 0)
        set->his_pos--;


	ft_putstr_fd("\033[1K",STDERR);
	ft_putstr_fd("\r",STDERR);
 	disp_prompt();

	

	ft_putstr_fd(set->history[set->his_pos], STDERR);
    //printf("\n\n\n [%s][%d] \n\n\n",set->history[set->his_pos], set->his_pos);
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
	size_t len;
	
	len = ft_strlen(set->str);

    if (set->his_pos < set->inc_his)
        set->his_pos++;

	ft_putstr_fd("\033[1K",STDERR);
	ft_putstr_fd("\r",STDERR);
 	disp_prompt();


	 
	ft_putstr_fd(set->history[set->his_pos], STDERR);
	return (0);
}
