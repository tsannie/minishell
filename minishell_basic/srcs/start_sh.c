/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/04 16:13:52 by phbarrad         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": command not found\n", 1);
}

void ft_putstr_error_quote(void)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd("syntax error with open quotes\n", 1);
}

char *get_val(void)
{
	char **line;
	int gnl;

	gnl = 0;
	line = malloc(sizeof(char *) * 1);
	gnl = get_next_line(0, line);
	//if (gnl == 0 && ft_strlen(*line) != 0)
	//	get_val();
	if (gnl == 0 && ft_strlen(*line) == 0)
	{
		//ft_putstr_fd("\nok\n", 1);
		//ft_putstr_fd("oui\n", 1);
		exit(127);
	}
	//printf("[%d]\n", gnl);
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

void	start_cmd(t_set *set)
{
	char *min;

	min = maj_to_min(set->cmd);
	//printf("min = {%s}\n", min);
	if (set->err_quote == 1)
		ft_putstr_error_quote();
	else if (ft_streql(set->cmd, "exit") == 1)
		ft_eexit(set);
	else if (ft_streql(min, "echo") == 1)
		ft_echo(set);
	else if (ft_streql(min, "cd") == 1)
		ft_cd(set);
	else if (ft_streql(min, "export") == 1)
		ft_export(set);
	else if (ft_streql(set->cmd, "unset") == 1)
		ft_unset(set);
	else if (ft_streql(min, "env") == 1)
		ft_env(set);
	else if (ft_streql(min, "clear") == 1)
		ft_putstr_fd("\033[H\033[2J", 1);
	else if (ft_strlen(min) != 0 && check_cmd(min) == 0 && bash_cmd(set) != 0)
	{
		//printf("[%d]\n",bash_cmd(set));
		ft_putstr_not_found(set->cmd);
		set->exit_val = 127;
	}
	free(min);
}

void	start_shell(int ac, char **av, t_set *set)
{
	if (ac == 3)
		set->str = av[2];// for testeur
	else
	{
		//ft_putstr_fd("avant", 1);
		set->str = get_val();
	}
	//set->str[ft_strlen(set->str) - 1] = '\0';
	//printf("[%s]\n", set->str);
	treat_cmd(set);
}

