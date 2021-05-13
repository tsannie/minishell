/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_bonus1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 09:52:57 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/13 10:27:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

t_sig			g_sig;

static void		int_handler(int sig)
{
	ft_putstr_fd("\b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_sig.run = 3;
	disp_prompt();
	(void)sig;
}

static void		initsis(t_set *set)
{
	g_sig.pid = -1;
	g_sig.run = 0;
	ffree(set->redirect);
	set->redirect = ft_strdup("");
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, int_handler);
}

static void			all_sdig(t_set *set)
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
		g_sig.run = 3;
	}
}

int				add_line(char *namefile, t_set *set)
{
	char		buf[BUF_SIZE];
	int			i;

	i = 0;
	initsis(set);
	if (g_sig.run == 0)
		ft_putstr_fd("> ", STDERR);
	while (i == 0)
	{
		all_sdig(set);
		start_term(set);
		if (g_sig.run == 3)
			return (ctrl_c(buf, set));
		ft_bzero((void *)buf, BUF_SIZE);
		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		set->fl = buf[1];
		if (all_ccmd2(buf, set) == 1)
			return (1);
		ft_putstr_fd(buf, STDERR);
		if (ft_strcmp(buf, "\n") == 0)
			i = 1;
	}
	if (g_sig.run == 3)
		return (ctrl_c(buf, set));
	if (ft_streql(namefile, set->redirect) == 1)
		return (1);
	return (0);
}

void			create_stdin(char *namefile, t_set *set)
{
	int		pipefd[2];
	int		exit;

	exit = 0;
	namefile = ft_strjoin_free(namefile, "\n");
	pipe(pipefd);
	set->redirect = ft_strdup("");
	while (exit == 0)
	{
		exit = add_line(namefile, set);
		if (exit == 0)
			ft_putstr_fd(set->redirect, pipefd[1]);
	}
	ffree(namefile);
	ifclose(pipefd[1]);
	if (exit == 2)
	{
		ifclose(pipefd[0]);
		set->stop = 1;
		return ;
	}
	ifclose(set->fdin);
	set->fdin = pipefd[0];
	dup2(set->fdin, STDIN);
}
