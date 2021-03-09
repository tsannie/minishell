/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 13:34:41 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void int_handler(int sig)
{
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	disp_prompt();
	//exit(0);
}

void		init_struct(t_set *set, char **av, char **envp)
{
	char	buff[4096 + 1];
	char 	*tmp;

	set->cmd = NULL;
	//set->shlvl = 2;
	set->exit_val = 0;
	set->fd = 1;
	/*int e = -1;
	 while (envp[++e])
		printf("-[%s]-\n", envp[e]);
	printf("\n\n"); */
	//print_args(envp);
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->pid = 0;

	set->old_pwd = ft_strjoin("OLDPWD=", "");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	ft_init_env(set, envp, av);

	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	//$?
	set->exit_v = ft_strjoin("?=", ft_itoa(set->exit_val));
	ft_modenv(set->exit_v, set);
	//$SHLVL
	tmp = ft_strjoin("SHLVL=", set->shlvl);
	ft_hideenv(tmp, set);
	ft_modenv(tmp, set);
	free(set->old_pwd);
	free(set->pwd);
}

int		ft_strlen_zero(char *str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while ((str[i] == '-' || str[i] == '+') && (str[i]))
		i++;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i + len] && (str[i + len] >= '0' && str[i + len] <= '9'))
		len++;
	return (len);
}

int		check_shlvl(t_set *set, char **envp)
{
	int i;
	int value;
	long long max =  9223372036854775807;
	unsigned long long val;

	val = 0;
	value = 0;
	set->shlvl = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			val = ft_atoill(envp[i] + 6);
			value = ft_atoi(envp[i] + 6);
		}
	}
	if (val > max)
		value = 0;
	if (value > 2147483646 || value < -2147483648)
		value = 0;
	else if (value < 0)
		value = 0;
	else if (value == 0)
		value = 1;
	else if (value > 200000 + 1)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR);
		ft_putnbr_fd(value + 1, STDERR);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR);
		value = 1;
	}
	else
		value += 1;
	set->shlvl = ft_strdup(ft_itoa(value));
	//printf("shlvl = [%s]val = [%d]\n", set->shlvl, value);
	return (0);
}

int			main(int ac, char **av, char **envp)
{
	t_set	*set;

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
			//printf("pid = %d", getpid());
			disp_prompt();
			start_shell(ac, av, set);
			//$?
			if (set->exit_v)
				free(set->exit_v);
			set->exit_v = ft_strjoin("?=", ft_itoa(set->exit_val));
			ft_modenv(set->exit_v, set);
		}
	}
	free(set);
	return (set->exit_val);
}
