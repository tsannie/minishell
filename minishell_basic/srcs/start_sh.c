/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/15 12:02:05 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_strcmpp(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] == ' ' || s1[i] == '\t')
		i++;
	while (s2[j] && s1[i] != ';') // ; = separe les commandes
	{
		if (s1[i] > s2[j])
			return (1);
		else if (s1[i] < s2[j])
			return (-1);
		j++;
		i++;
	}
	if (s1[i] == ' ' || s1[i] == '\t' || s1[i] == '\0' || s1[i] == ';')
		return (0);
	return (1);
}

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
	ft_putstr_fd("minish: ", 1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putstr_fd(": command not found\n", 1);
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
	while(res[i])
	{
		if (res[i] >= 'A' && res[i] <= 'Z')
			res[i] = res[i] + 32;
		i++;
	}
	return(res);
}

void	start_cmd(char **envp, t_set *set)
{
	char *min;

	min = maj_to_min(set->cmd);
	ft_eexit(set);
	if (ft_strcmpp(min, "echo") == 0)
		ft_echo(set);
	else if (ft_strcmpp(min, "cd") == 0)
		ft_cd(set);
	else if (ft_strcmpp(min, "pwd") == 0)
		ft_pwd(set);
	else if (ft_strcmpp(min, "export") == 0)
		ft_export(set, envp);
	else if (ft_strcmpp(min, "unset") == 0)
		ft_unset(set, envp);
	else if (ft_strcmpp(min, "env") == 0)
		ft_env(set, envp);
	else if (ft_strcmpp(min, "clear") == 0)
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

