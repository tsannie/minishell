/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 15:04:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void			disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void			int_handler(int sig)
{
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	disp_prompt();
}

void			init_struct(t_set *set, char **av, char **envp)
{
	char		buff[4096 + 1];
	char		*tmp;

	set->cmd = NULL;
	set->exit_val = 0;
	set->fd = 1;
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->pid = 0;
	set->old_pwd = ft_strjoin("OLDPWD=", "");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	tmp = ft_strjoin("SHLVL=", set->shlvl);
	set->exit_v = ft_strjoin("?=", ft_itoa(set->exit_val));

	ft_init_env(set, envp, av);
	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	//$?
	ft_modenv(set->exit_v, set);
	//$SHLVL
	ft_hideenv(tmp, set);
	ft_modenv(tmp, set);
	free(tmp);
	free(set->old_pwd);
	free(set->pwd);
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (check_shlvl(set, envp) != 0)
		return (-1);
	init_struct(set, av, envp);
	ft_sort_dbtab(set);
	if (ac == 3)		// for testeur
		start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		while (set->exit == 0)
		{
			disp_prompt();
			start_shell(ac, av, set);
		}
	}
	free(set);
	return (set->exit_val);
}
