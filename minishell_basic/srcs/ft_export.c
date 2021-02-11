/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:10:21 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/11 10:10:24 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char *concaenv(char *str)
{
    int j = 0;
    int y = 0;

    while (str[j]) {
        if (str[j] == ' '){
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
    int j = 0, e = 0, k = -1;

    while (str[k++])
    {
        if (str[k] == '=') {
            ft_putstr_fd("setenv: Variable name must contain", 1);
            ft_putstr_fd(" alphanumeric characters.\n", 1);
            return (1);
        }
    }
    while (str[j])
    {
        if (str[j] != ' ' && str[j+1] == ' ')
            e++;
        j++;
    }
    if (e == 3 || (e == 2 && str[j-1] != ' ')) {
        ft_putstr_fd("setenv: Too many arguments.\n", 1);
        return (1);
    }
    return (0);
}

int ft_setenv(char *str, char * envp[])
{
    int i = 0;
    int j = 0;

    while (str[j] != 'v' && str[j-1] != 'n')
        j++;
    j++;
    while (str[j] == ' ' || str[j] == '\t')
        j++;
    while (envp[i] != NULL)
        i++;
    if (checkenvp(str+j) == 1)
        return (1);
    envp[i] = space(str+j);
    envp[i] = concaenv(str+j);
    envp[i+1] = NULL;
    return (0);
}

int ft_export(t_set *set, char **envp)
{
	return (0);
}
