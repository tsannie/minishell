/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:27:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/22 17:39:03 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

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
	int				ret;
	char			*term_name;
	struct	winsize	w;
	struct	termios	term;


	if (!(term_name = getenv("TERM")))
		return (-1);
	if ((ret = tgetent(NULL, term_name)) <= 0)
		return (-1);
	if ((tcgetattr(STDIN_FILENO, &(term))) == -1)
		return (-1);
	if ((tcgetattr(STDIN_FILENO, &(term))) == -1)
		return (-1);
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[VEOL] = '\n';
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &(term))) == -1)
		return (-1);
	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) < 0)
		return (-1);
	if (tcsetattr(0, TCSANOW, &(term)) < 0)
		return (-1);
	set->col = w.ws_col;
	set->row = w.ws_row;
	set->winsize = set->col * set->row;
	if (check_termcaps() == -1)
		return (-1);
    return (0);
}
