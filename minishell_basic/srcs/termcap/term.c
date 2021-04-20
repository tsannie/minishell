/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:27:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 15:09:54 by phbarrad         ###   ########.fr       */
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
	struct winsize	w;

	if (!(term_name = getenv("TERM")))
		return (-1);
	if ((ret = tgetent(NULL, term_name)) <= 0)
		return (-1);
	if ((tcgetattr(STDIN_FILENO, &(set->term_save))) == -1)
		return (-1);
	if ((tcgetattr(STDIN_FILENO, &(set->termios))) == -1)
		return (-1);
	set->termios.c_lflag &= ~(ICANON | ECHO);
	set->termios.c_cc[VMIN] = 1;
	set->termios.c_cc[VTIME] = 0;
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &(set->termios))) == -1)
		return (-1);
	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) < 0)
		return (-1);
	set->col = w.ws_col;
	set->row = w.ws_row;
	set->winsize = set->col * set->row;
	if (check_termcaps() == -1)
		return (-1);
    return (0);
}

/* static const t_tab	g_tab_func[] =
{
	{"\022", ft_ctrlr},
	{"\033[A", ft_go_up},
	{"\033\033[A", ft_alt_up},
	{"\033[B", ft_go_down},
	{"\033\033[B", ft_alt_down},
	{"\033[C", ft_go_right},
	{"\033\033[C", ft_alt_right},
	{"\033[D", ft_go_left},
	{"\033\033[D", ft_alt_left},
	{"\033[H", ft_home},
	{"\001", ft_home},
	{"\033[F", ft_end},
	{"\005", ft_end},
	{"\012", ft_return},
	{"\011", ft_tab},
	{"\033[3~", ft_delete},
	{"\177", ft_backspace},
	{"\004", ft_exit_term},
	{"\013", ft_cut},
	{"\031", ft_paste},
	{"\014", ft_ctrll},
	{NULL, ft_print}
}; */
