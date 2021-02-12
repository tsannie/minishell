/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:10:21 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/12 13:29:20 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char *concaenv(char *str)
{
    int j = 0;
    int y = 0;

    while (str[j]) {
        if (str[j] == ' ')
		{
            str[j] = '=';
            return (str);
        }
        j++;
    }
    str[j] = '=';
    str[j+1] = '\0';
    return (str);
}

char *remplir_space(int av, int fin, char *str, char *str2)
{
    str[av+1] =  '\0';
    while (str2[fin] != ' ' && str2[fin] != '\t')
    {
        str[av] = str2[fin];
        av--;
        fin--;
    }
    return (str);
}

char *space(char *str)
{
    int e = -1, av = 0, inc = 0;
    int fin = ft_strlen(str);
    char *str2 = malloc(sizeof(char) * ft_strlen(str)+1);

    while (str[e++])
        str2[e] = str[e];
    while (str[av])
    {
        if (str[av] == ' ' || str[av] == '\t')
            inc++;
        av++;
    }
    av = av - inc + 1;
    if (inc == 0)
        return (str);
    return (remplir_space(av, fin, str, str2));
    return (str);
}

int checkenvp(char *str)
{
    int j = 0;
	int e = 0;
	int k;
	int egl;

	k = 1;
	egl = 0;
    while (str[k])
    {
        if ((str[k] == '=' && str[k - 1] != ' ') && (str[k] == '=' && str[k - 1] != ' '))
            egl++;
		k++;
    }
	//printf("[%d]\n", egl);
	if (egl == 0)
	{
		ft_putstr_fd("minishell: bad assignment\n", 1);
		return (1);
	}
	while (str[j])
    {
        if (str[j] != ' ' && str[j + 1] == ' ')
            e++;
        j++;
    }
    if (e == 3 || (e == 2 && str[j-1] != ' ')) {
        ft_putstr_fd("EXPORT: Too many arguments.\n", 1);
        return (1);
    }
	printf("[%s]\n", str);
    return (0);
}

int ft_setenv(t_set *set, char **envp)
{
    int i = 0;
    int j = 1;

    while (set->str[j] != 't' && set->str[j - 1] != 'r' && set->str[j])
        j++;
    j++;
    while (set->str[j] == ' ' || set->str[j] == '\t')
        j++;
    while (envp[i] != NULL)
        i++;
    if (checkenvp(set->str+j) == 1)
        return (1);

	envp[i]	= envp[i - 1];
	envp[i - 1] = set->str + j;	
	envp[i + 1] = NULL;
    return (0);
}

int	ft_exportenv(t_set *set)
{
    int i = 0;
    int j = 1;

    while (set->str[j] != 't' && set->str[j - 1] != 'r' && set->str[j])
        j++;
    j++;
    while (set->str[j] == ' ' || set->str[j] == '\t')
        j++;
    while (set->hide_envp[i] != NULL)
        i++;
	set->hide_envp[i]	= set->hide_envp[i - 1];
	set->hide_envp[i - 1] = set->str + j;	
	set->hide_envp[i + 1] = NULL;
    return (0);
}

int ft_disp_export(char **envp)
{
    int i = -1;
    while (envp[++i] != NULL)
        printf("declare -x %s\n", envp[i]);
    return (0);
}

int ft_export(t_set *set, char **envp)
{
    int i;
    int j;
	int egl;

	egl = 0;
	j = 0;
	i = 0;
	while (set->str[j])
	{
		if (set->str[j] == '=')
			egl = 1;
		j++;
	}
	printf("avant[%s]\n\n\n", set->str);
	if (egl == 1)
		ft_setenv(set, envp);
	else if (ft_strcmpp(set->str, "export e") == 0)//&& agr[0] == NULL)
		ft_disp_export(set->hide_envp);
	else
		ft_exportenv(set);
    return (0);
}