/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 09:52:57 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/12 13:00:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

t_sig			g_sig;

static void			int_handler(int sig)
{
	ft_putstr_fd("\b\b", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_sig.run = 3;
	disp_prompt();
	(void)sig;
}

static void			sig_quit(int code)
{
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putnbr_fd(code, STDERR);
		ft_putstr_fd("\n", STDERR);
		g_sig.run = 3;
	}
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

static void			initsis(t_set *set)
{
	g_sig.pid = -1;
	g_sig.run = 0;
	ffree(set->redirect);
	set->redirect = ft_strdup("");
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, int_handler);
	ft_putstr_fd("ici2\n", STDERR);
}

static int			ft_dell2(t_set *set)
{
	size_t		len;
	size_t		col;

	col = set->col;
	len = ft_strlen(set->redirect);
	set->redirect = ft_strdup_free_len(set->redirect, len);
	set->dell_len = getdellen(len + 12, col);
	if ((len + 12) == col)
	{
		ft_putstr_fd(set->tt_up, STDERR);
		ft_putstr_fd("\033[2K", STDERR);
		ft_putstr_fd("> ", STDERR);
		ft_putstr_fd(set->redirect, STDERR);
	}
	else if (((len + 12) % col) == 0 && ((len + 12) >= col * 2))
	{
		ft_putstr_fd(set->tt_up, STDERR);
		ft_putstr_fd("\033[2K", STDERR);
		ft_putstr_fd(set->redirect + ((col * set->dell_len) - 12), STDERR);
	}
	else if (len > 0)
		aff_dell(set);
	return (0);
}

static int			all_ccmd2(char *buf, t_set *set)
{
	if (buf[0] == 127 && ft_strlen(buf) == 1)
		buf[0] = ft_dell2(set);
	else if (buf[0] == 9 && ft_strlen(buf) == 1)
		buf[0] = 0;
	else if (ft_strlen(buf) == 3 && buf[0] == 27)
	{
		buf[0] = 0;
		buf[1] = 0;
	}
	else if (ft_strlen(buf) == 1 && buf[0] == 4)
	{
		if (ft_strlen(set->redirect) == 0)
		{
			buf[0] = 0;
			return (1);
		}
	}
	else
		set->redirect = ft_strjoin_free(set->redirect, buf);
	return (0);
}

int					add_line(char *namefile, t_set *set)
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
		{
			set->credir = ft_strdup(buf);
			return (2);
		}
		ft_bzero((void *)buf, BUF_SIZE);
		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		if (all_ccmd2(buf, set) == 1)
			return (1);
		ft_putstr_fd(buf, STDERR);
		if (ft_strcmp(buf, "\n") == 0)
			i = 1;
	}
	//g_sig.pid = 0;
	//printf("[%d]\n", g_sig.run);

	if (ft_streql(namefile, set->redirect) == 1)
		return (1);
	return (0);
}

void	create_stdin(char *namefile, t_set *set)
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
	ifclose(pipefd[1]);
	if (exit == 2)
	{
		ifclose(pipefd[0]);
			//	ft_putstr_fd("w8\n", STDERR);

		set->stop = 1;
		return ;
	}
	ifclose(set->fdin);
	set->fdin = pipefd[0];
	dup2(set->fdin, STDIN);
}
