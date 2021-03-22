/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/22 13:07:02 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int				g_run = 0;
int				g_pid = -1;

void			disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void			int_handler(int sig)
{
	//printf("avant2?");
	//printf("avant22?");
	//printf("sig = [%d]\n", sig);
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_run = 1;
	disp_prompt();
}

void	sig_quit(int code)
{
	//char	*nbr;
	//printf("pid = [%d]\n", g_pid);

	//nbr = ft_itoa(code);
	if (g_pid == 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putnbr_fd(code, STDERR);
		ft_putstr_fd("\n", STDERR);
		g_run = 3;
		disp_prompt();
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

void			init_struct(t_set *set, char **av, char **envp)
{
	char		buff[4096 + 1];
	char		*tmp;
	char		*tmp2;

	set->cmd = NULL;
	set->pathbc = NULL;
	set->lastcmd = NULL;
	set->all_path = NULL;
	set->exit_val = 0;
	set->pid = 0;
	set->save_stdout = dup(STDOUT);			// ok
	set->save_stdin = dup(STDIN);			// check that
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->old_pwd = ft_strjoin("OLDPWD=", "");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	tmp = ft_strjoin("SHLVL=", set->shlvl);
	tmp2 = ft_itoa(set->exit_val);
	set->exit_v = ft_strjoin("?=", tmp2);
	set->all_path = ft_splitbc(set->path, ':');

	ft_init_env(set, envp, av);

	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	
	ft_hideenv(set->exit_v, set);
	ft_hideenv(tmp, set);
	
	ft_modenv(tmp, set);
	
	ft_unsethideenv(set, "OLDPWD");
	ft_unsetenv(set, "OLDPWD");
	
	free(tmp2);
	free(tmp);
}

void			add_exval(t_set *set)
{
	char *tmp;

	tmp = ft_itoa(set->exit_val);
	if (set->exit_v)
		free(set->exit_v);
	set->exit_v = ft_strjoin("?=", tmp);
	free(tmp);
	ft_hideenv(set->exit_v, set);
}

/* int init_term(void)
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }
    ret = tgetent(NULL, term_type);
    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
        return -1;
    }
    return 0;
}
 */

int				main(int ac, char **av, char **envp)
{
	t_set	*set;
	int		term;

    //char *term_type = getenv("TERM");

    //term = tgetent(NULL, term_type);
	if (term == -1)
		return (-1);
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
		signal(SIGQUIT, sig_quit);
		while (1)
		{
			if (g_run == 0)
				disp_prompt();
			if (ac == 3)
				set->str = av[2];		// for testeur
			else
				set->str = get_val(set);
			if (g_run == 1)
			{
				set->exit_val = g_run;
				add_exval(set);
				g_run = 0;
			}
			else if (g_run == 3)
			{
				set->exit_val = 131;
				add_exval(set);
				g_run = 0;
			}
			g_pid = 0;
			treat_cmd(set);
			g_pid = -1;
		}
	}
	free(set);
	return (set->exit_val);
}
