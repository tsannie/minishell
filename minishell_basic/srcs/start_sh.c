/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/16 10:21:34 by tsannie          ###   ########.fr       */
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

	line = malloc(sizeof(char *) * 2);
	get_next_line(0, line);
	return (*line);
}

char	*maj_to_min(char *str)
{
	int i;
	char *res;

	res = ft_strdup(str);
	i = 0;
	while (res[i])
	{
		if (res[i] >= 'A' && res[i] <= 'Z')
			res[i] = res[i] + 32;
		i++;
	}
	return (res);
}

void	start_cmd(char **envp, t_set *set)
{
	char *min;

	min = maj_to_min(set->cmd);
	printf("min = {%s}\n", min);
	if (set->err_quote == 1)
		ft_putstr_error_quote();
	else if (ft_streql(min, "exit") == 1)
		ft_eexit(set);
	else if (ft_streql(min, "echo") == 1)
		ft_echo(set);
	else if (ft_streql(min, "cd") == 1)
		ft_cd(set);
	else if (ft_streql(min, "pwd") == 1)
		ft_pwd(set);
	else if (ft_streql(min, "export") == 1)
		ft_export(set, envp);
	else if (ft_streql(min, "unset") == 1)
		ft_unset(set, envp);
	else if (ft_streql(min, "env") == 1)
		ft_env(set, envp);
	else if (ft_streql(min, "clear") == 1)
		ft_putstr_fd("\033[H\033[2J", 1);
	else if (ft_strlen(min) != 0 && check_cmd(min) == 0)
		ft_putstr_not_found(set->cmd);
	free(min);
}

void	start_shell(int ac, char **av, char **envp, t_set *set)
{
	if (ac == 3)
		set->str = av[2];// for testeur
	else
		set->str = get_val();
	treat_cmd(set, envp);
}

