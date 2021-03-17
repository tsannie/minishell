/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/17 10:53:55 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int check_cmd(char *str)
{
    int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void ft_putstr_not_found(char *str)
{
	int i;

	i = 0;
	ft_putstr_fd("minishell: ", 1);							// peut etre placer sous STDER
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": command not found\n", 1);
}

void ft_putstr_error_quote(void)
{
	ft_putstr_fd("minishell: ", 1);							// peut etre placer sous STDER
	ft_putstr_fd("syntax error with open quotes\n", 1);
}

char *get_val(void)
{
	char **line;
	int gnl;

	gnl = 0;
	line = malloc(sizeof(char *) * 1);
	gnl = get_next_line(0, line);
	//printf("[%d][%s]\n", gnl, *line);
	if (gnl == 0 && ft_strlen(*line) != 0)
		ft_putstr_fd("\b\b  ", STDERR);
	if (gnl == 0 && ft_strlen(*line) == 0)
	{
		ft_putstr_fd("exit\n", 1);			// peut etre placer sous STDER
		exit(0);
	}
	return (*line);
}

char	*maj_to_min(char *str)
{
	int i;
	char *res;

	i = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		if (res[i] >= 'A' && res[i] <= 'Z')
			res[i] = res[i] + 32;
		i++;
	}
	return (res);
}

int		eglinstr(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	get_lastcmd(t_set *set)
{
	int i;
	char *tmp;

	i = 0;
	while (set->str[i])
	{
		if (ft_strncmp(set->str + i, "$_", 2) == 0 && set->lastcmd != NULL)
		{
			//printf("oui = [%s]\n", set->lastcmd);
			ft_hideenv(set->lastcmd, set);
			ft_modenv(set->lastcmd, set);
			return ;
		}
		i++;
	}
	i = 0;

	while (set->arg[i])
		i++;
	if (set->arg[0] == NULL)
		tmp = ft_strdup(set->cmd);
	else if (i != 0)
		tmp = ft_strdup(set->arg[i - 1]);
 	if (ft_strncmp(set->cmd, "export", ft_strlen(set->cmd)) == 0 && eglinstr(tmp) == 1 && i != 0)
	{
		if (tmp)
			free(tmp);
		tmp = before_equale(set->arg[i - 1]);
		//printf("[%s]\n", tmp);
	}

	//printf("pathbc = [%s]\n", set->pathbc);
/*  	if (set->pathbc != NULL)
	{
		free(set->pathbc);
		set->pathbc = NULL;
	}
 	else
	{*/
		//set->lastcmd = joinf("_=", set->pwd + 4, "/", tmp);
		if (set->lastcmd)
			free(set->lastcmd);
		set->lastcmd = ft_strjoin("_=", tmp);
		if (tmp)
			free(tmp);
		//ft_hideenv(set->lastcmd, set);
		ft_modenv(set->lastcmd, set);
		//printf("last = [%s]\n", set->lastcmd);
		if (set->lastcmd)
		{
			free(set->lastcmd);
			set->lastcmd = NULL;
		}
	//}
}

void	start_cmd(t_set *set)
{
	char *min;

	//print_args(set->arg);
	min = maj_to_min(set->cmd);
	get_lastcmd(set);
	if (bash_cmd(set, min) == 0)
		;
	else if (set->err_quote == 1)
		ft_putstr_error_quote();
	else if (ft_streql(set->cmd, "exit") == 1)
		ft_eexit(set);
	else if (ft_streql(set->cmd, "pwd") == 1)
		ft_pwd(set);
	else if (ft_streql(set->cmd, "cd") == 1)
		ft_cd(set);
	else if (ft_streql(set->cmd, "export") == 1)
		ft_export(set);
	else if (ft_streql(set->cmd, "unset") == 1)
		ft_unset(set);
	else if (ft_streql(set->cmd, "env") == 1)
		ft_env(set);
	else if (ft_streql(set->cmd, "clear") == 1)
		ft_putstr_fd("\033[H\033[2J", 1);
	else if (ft_streql(set->cmd, "echo") == 1)
	{
		ft_echo(set);
	}
	else if (ft_strlen(set->cmd) != 0 && check_cmd(set->cmd) == 0)
	{
		//printf("MON\n");
		ft_putstr_not_found(set->cmd);
		set->exit_val = 127;
	}
/* 	char *tmp;
	if (set->pathbc)
		free(set->pathbc);
	else
	{
		tmp = joinf("_=", set->pwd, "/", set->lastcmd);
		ft_modenv(tmp, set);
		free(tmp);
	} */
	add_exval(set);
/* 	if (set->pathbc != NULL)
	{
		free(set->pathbc);
		set->pathbc = NULL;
	}  */
	//printf("nf[%d]\n", set->exit_val);
	//printf("after = [%s]\n", set->lastcmd);
	free(min);
	free(set->cmd);
	ft_free_dbtab(set->arg);
	ifclose(set->pipein);
	ifclose(set->pipeout);
	set->pipein = -1;
	set->pipeout = -1;
}

void	start_shell(int ac, char **av, t_set *set)
{
	if (ac == 3)
		set->str = av[2];		// for testeur
	else
	{
		//ft_putstr_fd("avant",  set->fd);
		set->str = get_val();
	}
	//set->str[ft_strlen(set->str) - 1] = '\0';
	//printf("[%s]\n", set->str);
	treat_cmd(set);
}

