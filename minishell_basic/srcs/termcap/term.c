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

int		        start_term(t_set *set)
{
    int         ret;
    char        *term_name;

    ret = 0;
	if (!(term_name = getenv("TERM")))
		ft_putstr_fd("getenv error\n", STDERR);
    if ((ret = tgetent(NULL, term_name)) <= 0)
		ft_putstr_fd("tgtent err\n", STDERR);
    printf("getenv = [%s][%d]\n", term_name, ret);
    return (0);
}