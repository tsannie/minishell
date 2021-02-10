/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 14:29:49 by phbarrad         ###   ########.fr       */
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

	line = malloc(sizeof(char *) * 1);
	get_next_line(0, line);
    return (*line);
}

void	start_shell(int ac, char **av, char **envp, t_set *set)
{
	set->str = get_val();
	if (ft_strcmpp(set->str, "exit") == 0)
        exit(0);
	else if (ft_strcmpp(set->str, "echo") == 0)
        ft_echo(set);
	else if (ft_strcmpp(set->str, "cd") == 0)
        ft_cd(set);
	else if (ft_strcmpp(set->str, "pwd") == 0)
		ft_pwd(set);
	else if (ft_strcmpp(set->str, "export") == 0)
		ft_export(set);
	else if (ft_strcmpp(set->str, "unset") == 0)
		ft_unset(set, envp);
	else if (ft_strcmpp(set->str, "env") == 0)
		ft_env(set, envp);
	else if (ft_strcmpp(set->str, "clear") == 0)
		ft_putstr_fd("\033[H\033[2J", 1);
    else if (ft_strlen(set->str) != 0 && check_cmd(set->str) == 0)
		ft_putstr_not_found(set->str);
}