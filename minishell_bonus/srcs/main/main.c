/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:13:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

t_sig			g_sig;

void			disp_prompt(void)
{
	ft_putstr_fd("\033[1;35mᴍ\033[1;33mɪ\033[1;31mɴ\033[1;36mɪ", STDERR);
	ft_putstr_fd("\033[1;32msʜᴇʟʟ\033[1;37m ➔\033[0m  ", STDERR);
}

void			int_handler(int sig)
{
	ft_putstr_fd("\b\b  ", STDERR);
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
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;

	int ret;
	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);
	g_sig.pid = 0;
	g_sig.run = 0;
	ret = 0;
	if (ac == 3)
		ret = start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, sig_quit);
		while (1)
		{
			if (g_sig.run == 0)
				disp_prompt();
			//read_ent(set);
			set->str = get_val(set);
			if (g_sig.run == 1)
			{
				set->exit_val = g_sig.run;
				add_exval(set);
				g_sig.run = 0;
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
	}
	return (ret);
}