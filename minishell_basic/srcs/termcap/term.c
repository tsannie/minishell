/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:27:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"
#include <curses.h>
#include <term.h>

static int	check_termcaps(void)
{
	if (!(tgetstr("do", NULL)))
		return (-1);
	if (!(tgetstr("up", NULL)))
		return (-1);
	if (!(tgetstr("le", NULL)))
		return (-1);
	if (!(tgetstr("nd", NULL)))
		return (-1);
	if (!(tgetstr("cr", NULL)))
		return (-1);
	if (!(tgetstr("cd", NULL)))
		return (-1);
	if (!(tgetstr("cl", NULL)))
		return (-1);
	if (!(tgetstr("sc", NULL)))
		return (-1);
	if (!(tgetstr("rc", NULL)))
		return (-1);
	if (!(tgetstr("UP", NULL)))
		return (-1);
	if (!(tgetstr("DO", NULL)))
		return (-1);
	return (0);
}
int		        start_term(t_set *set)
{
/*     int         ret;
    char        *term_name;

    ret = 0;
	if (!(term_name = getenv("TERM")))
		ft_putstr_fd("getenv error\n", STDERR);
    if ((ret = tgetent(NULL, term_name)) <= 0)
		ft_putstr_fd("tgtent err\n", STDERR);
    if ((tcgetattr(0, &(set->term_save))) == -1)
		ft_putstr_fd("tcg err\n", STDERR);
    if ((tcgetattr(0, &(set->termios))) == -1)
		ft_putstr_fd("tcg err\n", STDERR);
	if ((tcsetattr(0, 1, &(set->termios))) == -1)
		ft_putstr_fd("tcg err\n", STDERR);
    if (check_termcaps() == -1)
        return (-1); */
    //printf("getenv = [%s][%d]\n", term_name, ret);
    return (0);
}