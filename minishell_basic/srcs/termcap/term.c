/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:27:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/23 16:07:36 by phbarrad         ###   ########.fr       */
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

void		start_term(t_set *set)
{
	int				ret;
	char			*term_name;
	struct winsize	w;

	if (!(term_name = getenv("TERM")))
		ft_putstr_fd("ERR\n", STDERR);
	if ((ret = tgetent(NULL, term_name)) <= 0)
		ft_putstr_fd("ERR\n", STDERR);
	if ((tcgetattr(STDIN_FILENO, &(set->term_backup))) == -1)
		ft_putstr_fd("ERR\n", STDERR);
	if ((tcgetattr(STDIN_FILENO, &(set->term))) == -1)
		ft_putstr_fd("ERR\n", STDERR);
	set->term.c_lflag &= ~(ICANON | ECHO);
	set->term.c_cc[VMIN] = 1;
	set->term.c_cc[VTIME] = 0;
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &(set->term))) == -1)
		ft_putstr_fd("ERR\n", STDERR);
	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) < 0)
		ft_putstr_fd("ERR\n", STDERR);
	set->col = w.ws_col;
	set->row = w.ws_row;
	set->winsize = set->col * set->row;
	if (check_termcaps() == -1)
		ft_putstr_fd("ERR\n", STDERR);
}

/*void		start_term(t_set *set)
{
	char	*name;

	if (!(name = get_env(g_minishell, "TERM")))
		name = "xterm";
	tgetent(NULL, name);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &set->term);
	tcgetattr(0, &set->term_backup);
	set->term.c_lflag = set->term.c_lflag & ~ICANON;
	set->term.c_lflag = set->term.c_lflag & ~ECHO;
	set->term.c_cc[VMIN] = 1;
	set->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &set->term);
	init_tc();
}

void	cursor_win(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	set->col = w.ws_col;
	set->row = w.ws_row;
}

void	init_tc(void)
{
	set->->cm = tgetstr("cm", NULL);
	set->->ce = tgetstr("ce", NULL);
	set->->dl = tgetstr("DL", NULL);
}*/