/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:39 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/08 10:34:07 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char *ft_getenv(void)
{
    char *cwd;
	char *result;
	char buff[4096 + 1];
    int i = 0;
	int e = -2;
	int r = -3;

    cwd = getcwd(buff, 4097);
	result = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
    while (cwd[i])
    {
        if (cwd[i] == '/')
            e++;
        i++;
    }
    while (e > 0)
    {
        r += 3;
        result[r] = '.';
        result[r+1] = '.';
        result[r+2] = '/';
        e--;
    }
    result[r+3] = '\0';
    return (result);
}

int		real_path(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	i += 2; // + cd
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int		ft_cd(t_set *set)
{
	int valid;
	char	buff[4096 + 1];

/* 	int x = -1;
	while (set->arg[++x])
		printf("[%s]\n", set->arg[x]);
	printf("[%s]\n", set->arg[x]); */
	if (set->old_pwd)
		free(set->old_pwd);
	set->old_pwd = ft_strdup(set->pwd);
	free(set->pwd);
	set->pwd = ft_strdup(getcwd(buff, 4097));
	ft_hideenv(ft_strjoin("PWD=", set->pwd), set);
	ft_modenv(ft_strjoin("PWD=", set->pwd), set);
	ft_hideenv(ft_strjoin("OLDPWD=", set->old_pwd), set);
	ft_modenv(ft_strjoin("OLDPWD=", set->old_pwd), set);
	if (set->arg[0] != NULL)
		valid = chdir(set->arg[0]);
	if (valid == -1 && set->arg[0] != NULL)
	{
		//if (set->arg[0] == NULL)
		printf("minishell: cd: %s: No such file or directory\n", set->arg[0]);
	}
	if (set->arg[0] == NULL)
		return (chdir(ft_getenv()));
    return (0);
}