/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:12:42 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	err_amb(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->dol_amb, STDERR);
	ft_putstr_fd(": ambiguous redirect\n", STDERR);
	set->stop = 1;
	set->exit_val = 1;
	set->bleu = 1;
}

void	err_notexist(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->namefile, STDERR);
	if (set->not_exist == 1)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	else if (set->not_exist == 2)
		ft_putstr_fd(": Is a directory\n", STDERR);
	else if (set->not_exist == 3)
		ft_putstr_fd(": Not a directory\n", STDERR);
	ffree(set->namefile);
	set->stop = 1;
	set->exit_val = 1;
	set->bleu = 1;
}

void	check_err_and_incr(t_set *set, int *i)
{
	if (set->amb == 1)
		err_amb(set);
	else if (set->not_exist == 1 || set->not_exist == 2 || set->not_exist == 3)
		err_notexist(set);
	*(i) = *(i) + 1;
}
