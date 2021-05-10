/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgent.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/29 14:28:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

t_sig			g_sig;

void			int_handler(int sig)
{
	ft_putstr_fd("\b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_sig.run = 1;
	(void)sig;
	disp_prompt();
}

void			sig_quit(int code)
{
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putnbr_fd(code, STDERR);
		ft_putstr_fd("\n", STDERR);
		g_sig.run = 3;
	}
}

void			all_sdig(t_set *set)
{
	if (g_sig.run == 1)
	{
		set->exit_val = g_sig.run;
		add_exval(set);
		g_sig.run = 0;
		ffree(set->str);
		set->str = ft_strdup("");
	}
	else if (g_sig.run == 3)
	{
		set->exit_val = 131;
		set->bleu = 1;
		add_exval(set);
		g_sig.run = 0;
	}
}

void			initsis(t_set *set)
{
	g_sig.pid = -1;
	g_sig.run = 0;
	ffree(set->str);
	set->str = ft_strdup("");
	set->cur_pos = 12;
	signal(SIGINT, int_handler);
	signal(SIGQUIT, sig_quit);
}

void			aff_buf(t_set *set, char *buf)
{
	size_t len;
	int r = 0;
	int e = 0;
	size_t col = set->col;
	len = ft_strlen(set->str);
	ft_putstr_fd(buf, STDERR);
}

void			read_ent(t_set *set)
{
	char		buf[BUF_SIZE];
	int			i;

	i = 0;
	initsis(set);
	if (g_sig.run == 0)
		disp_prompt();
	while (i == 0)
	{
		start_term(set);
		ft_bzero((void *)buf, BUF_SIZE);
		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		all_sdig(set);
		all_ccmd(buf, set);
		if (ft_strcmp(buf, "\n") == 0)
			i = 1;
	}
	eeddn(set);
	g_sig.pid = 0;
}
