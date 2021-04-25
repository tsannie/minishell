/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:13:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/25 18:21:03 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

t_sig			g_sig;

void			disp_prompt(void)
{
	ft_putstr_fd("\033[1;35mᴍ\033[1;33mɪ\033[1;31mɴ\033[1;36mɪ", STDERR);
	ft_putstr_fd("\033[1;32msʜᴇʟʟ\033[1;37m ➔\033[0m ", STDERR);
}

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
		disp_prompt();
	}
}

void			all_sig(t_set *set)
{
	if (g_sig.run == 0)
		disp_prompt();
	read_ent(set);
	if (g_sig.run == 1)
	{
		set->exit_val = g_sig.run;
		add_exval(set);
		g_sig.run = 0;
		ffree(set->str);
		set->str = ft_strdup("");
		printf("[%s]\n", set->str);
	}
	else if (g_sig.run == 3)
	{
		set->exit_val = 131;
		set->bleu = 1;
		add_exval(set);
		g_sig.run = 0;
	}
	g_sig.pid = 0;
	treat_cmd(set);
	g_sig.pid = -1;
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;
	int			ret;
	int x;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);
	g_sig.pid = 0;
	g_sig.run = 0;
	ret = 0;
	x = -1;
	if (ac == 3)
		ret = start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, sig_quit);
		while (1)
			all_sig(set);
	}
	return (ret);
}
