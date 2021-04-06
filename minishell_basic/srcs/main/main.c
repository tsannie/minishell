/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:56:40 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/01 14:47:26 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

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

void			read_ent(t_set *set)
{
	ffree(set->str);
	set->str = get_val(set);
 	//printf("setstr = [%s] len = [%d]\n", set->str, ft_strlen(set->str));
	if (set->str != NULL)
	{
		if (ft_strlen(set->str) > 0)
		{
			if (set->inc_his == 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
			}
			else if (ft_strcmp(set->history[set->inc_his - 1], set->str) != 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
			}
		}
	}
	/* int x = -1;
	while (set->history[++x])
		printf("[%s]\n", set->history[x]); */
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;
	int		parse;
	char	buf[BUF_SIZE];
	size_t	buf_len;

	int ret;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);
	g_sig.pid = 0;
	g_sig.run = 0;
	ret = 0;
	if (ac == 3)
	{
		ret = start_shell(ac, av, set);
		//exit(0);
		//printf("apres\n");
		//free_all(set, set->exit_val);
	}
	else
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, sig_quit);
		while (1)
		{
			if (g_sig.run == 0)
				disp_prompt();
			read_ent(set);
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