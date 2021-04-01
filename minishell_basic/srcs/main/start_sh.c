/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../includes/minish.h"

/*int check_cmd(char *str)
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
}*/

void ft_putstr_not_found(char *str, t_set *set)
{
	//printf("paath = [%s]\n", set->path);
	if (set->path == NULL)
		set->exit_val = 6;
	else if (ft_strlen(set->path) == 0)
		set->exit_val = 6;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	if (set->exit_val == 3)
	{
		ft_putstr_fd(": is a directory\n", STDERR);
		set->exit_val = 126;
	}
	else if (set->exit_val == 4)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR);
		set->exit_val = 126;
	}
	else if (set->exit_val == 6)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR);
		set->exit_val = 127;
	}
	else if (set->exit_val == 5)
	{
		ft_putstr_fd(": Permission denied\n", STDERR);
		set->exit_val = 126;
	}
	else if (set->exit_val == 7)
	{
		ft_putstr_fd(": Not a directory\n", STDERR);
		set->exit_val = 126;
	}
	else
	{
		ft_putstr_fd(": command not found\n", STDERR);
		set->exit_val = 127;
	}
	set->bleu = 1;
}

void ft_putstr_error_quote(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);							// peut etre placer sous STDER
	ft_putstr_fd("syntax error with open quotes\n", STDERR);
	set->exit_val = 2;
	set->bleu = 1;
}

char *get_val(t_set *set)
{
	char *line;
	int gnl;

	gnl = 0;
	line = NULL;
	gnl = get_next_line(0, &line, set);
	if (gnl == 0 && ft_strlen(line) != 0)
		ft_putstr_fd("\b\b  ", STDERR);
	if (gnl == 0 && ft_strlen(line) == 0)
	{
		ft_putstr_fd("exit\n", STDERR);
		exit(0);
	}
	return (line);
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


int		check_last(t_set *set)
{
	int i;
	// $_ && echo $_ && qwe qwe qwe $_
	if (ft_strncmp(set->str, "$_", ft_strlen(set->str)) == 0)//&& set->lastcmd != NULL)
	{
			//printf("oui 1\n");
			return (1);
	}

	i = ft_strlen(set->str) - 1;
	//printf("c = [%c]\n", set->str[i]);
	while (set->str[i] == ' ' || set->str[i] == '\t')
		i--;
	//printf("s - 1 = [%s]\n", set->str + i - 1);
	if (ft_strncmp(set->str + i - 1, "$_", 2) == 0)//&& set->lastcmd != NULL)
	{
		//printf("oui 2\n");
		return (1);
	}
	return (0);
}

void	get_lastcmd(t_set *set)
{
	int i;
	char *tmp;

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

		ffree(set->lastcmd);
		set->lastcmd = ft_strjoin("_=", tmp);
		if (tmp)
			free(tmp);
		ft_hideenv(set->lastcmd, set);
		ft_modenv(set->lastcmd, set);
		//printf("las1 = [%s]\n", set->lastcmd);
	//}
}

void	start_cmd(t_set *set)
{
	char *min;

	//printf("cmd = {%s}\n", set->cmd);
	//print_args(set->arg);
	min = maj_to_min(set->cmd);
	get_lastcmd(set);
	add_exval(set);
	if (ft_streql(set->cmd, "exit") == 1)
		ft_eexit(set);
	if (set->bleu == 1)
	{
		set->exit_val = 0;
		set->bleu = 0;
	}
	if (set->err_quote == 1)
		ft_putstr_error_quote(set);
	else if (ft_streql(set->cmd, "export") == 1)
		ft_export(set);
	else if (ft_streql(set->cmd, "cd") == 1)
		ft_cd(set);
	else if (ft_streql(set->cmd, "pwd") == 1)
		ft_pwd(set);
	else if (ft_streql(set->cmd, "unset") == 1)
		ft_unset(set);
	else if (ft_streql(set->cmd, "echo") == 1)
		ft_echo(set);
	else if (ft_streql(set->cmd, "env") == 1)
		ft_env(set);
	else if (bash_cmd(set, min) == 0)
		;
	else if (ft_strlen(set->cmd) != 0 && set->ex_er == 0)
	{
		if (ft_strncmp(set->cmd + ft_strlen(set->cmd) - 1, "/",
		ft_strlen(set->cmd + ft_strlen(set->cmd) - 1)) == 0 &&
		set->exit_val != 3 && set->exit_val != 7)
			set->exit_val = 4;
		ft_putstr_not_found(set->cmd, set);
		set->bleu = 1;
	}
	set->ex_er = 0;
	if (set->bleu == 2)
		set->bleu = 1;
	if (set->path)
		free(set->path);
	set->path = ft_get_path(set->envp);
	if (set->all_path)
		ft_free_dbtab(set->all_path);
	set->all_path = ft_splitbc(set->path, ':');
	add_exval(set);
 	free(min);
}

int	start_shell(int ac, char **av, t_set *set)
{
	int ret;
	if (ac == 3)
		set->str = ft_strdup(av[2]);
	treat_cmd(set);
	ret = set->exit_val;
	return (ret);
}

