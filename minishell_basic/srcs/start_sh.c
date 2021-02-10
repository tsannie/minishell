/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 13:34:06 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../includes/minish.h"

int ft_strcmpp(char *s1, char *s2)
{
    int i = 0, j = 0;

    while (s2[j] && s1[j] != ';') // ; = separe les commandes
    {
        if (s1[j] > s2[j])
            return (1);
        else if (s1[j] < s2[j])
            return (-1);
        j++;
    }
    if (s1[j] == ' ' || s1[j] == '\t' || s1[j] == '\0' || s1[j] == ';')
        return (0);
    return (1);
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

	//ft_putstr_fd(set->str, 1);

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
}