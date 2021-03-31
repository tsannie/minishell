/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:56:40 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
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

int				main(int ac, char **av, char **envp)
{
	t_set		*set;
	//int			keycode;
	int ret;
	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);//free_all(set, -1));

/* 	char *ku;
	char *kd;

	char *cl_string;
	char *cm_string;
	int auto_wrap;
	int height;
	int width;
	char *temp;
	char *BC;
	char *UP;
	char *DO;
 */
	//int x;
	if (init_tgent(set) == -1)
		return (-1);
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
			//if (read_stdin(&keycode) < 0)
			//	return (-1);
			//ft_putnbr_fd(keycode, STDERR);
			if (g_sig.run == 0)
				disp_prompt();
			if (set->str)
				free(set->str);
			set->str = get_val(set);
			if (set->str)
			{
				if (ft_strlen(set->str) != 0)
				{
					set->inc_his++;
					set->history = addword(set->history, set->inc_his, set->str);
				}
			}
/* 		x = -1;
			while (set->history[++x])
<<<<<<< HEAD
				printf("his = [%s]\n", set->history[x]); */
				//printf("his = [%s]\n", set->history[x]);
			//set->line_count = tgetnum("li");
			//printf("line_count = [%d]\n", set->line_count);
/* 			ku = tgetstr("ku", NULL);
			kd = tgetstr("kd", NULL);

			printf("\n\n\n\nku  [%s]==[%s]\n\n\n\n\n",set->cmd, ku);
			printf("\n\n\n\nkd  [%s]==[%s]\n\n\n\n\n",set->cmd, kd);

			//cl_string = tgetstr("cl", NULL);
			cm_string = tgetstr("cm", NULL);
			auto_wrap = tgetflag("am");
			height = tgetnum("li");
			width = tgetnum("co");
			temp = tgetstr("pc", NULL);
			BC = tgetstr("le", NULL);
			UP = tgetstr("up", NULL);
			DO = tgetstr("do", NULL); */
			//printf("\n\n\n[%s][%d][%d][%d][%s][%s]\n\nup = [%s]\n\ndo = [%s]\n\n", cm_string, auto_wrap,height,width,temp,BC,UP,DO);
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

		//printf("[%s]\n", set->pwd);
/* 
 	free(set->tt_up);
	free(set->tt_down);
	free(set->tt_left);
	free(set->tt_right);
	free(set->tt_home);
	free(set->tt_end);
	free(set->tt_ctl_up);
	free(set->tt_crl_down);


  	//ffree(set->str);
	ffree(set->word_tmp);
	ffree(set->dol_amb);
	//ffree(set->namefile);
	//ffree(set->pathbc);
	//ffree(set->pwd);


	//ffree(set->cmd);
	//ffree(set->path);
	//ffree(set->lastcmd);
	//ffree(set->exit_v);
	//ffree(set->shlvl);
	//ffree(set->old_pwd);

 	//ft_free_dbtab(set->list);
	//ft_free_dbtab(set->push);
	//ft_free_dbtab(set->history);

	ft_free_dbtab(set->all_path);
	ft_free_dbtab(set->hide_envp);
	ft_free_dbtab(set->envp);  
	//ft_free_dbtab(set->arg);
 
	//printf("arg = [%s]\n", set->arg[0]);
	//print_args(set->envp);

	
	//print_args(set->envp);
	//printf("----[%s]\n", set->pwd);



	free(set); */
	return (ret);
}
