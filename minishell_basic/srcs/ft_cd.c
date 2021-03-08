/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:39 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/08 13:49:53 by phbarrad         ###   ########.fr       */
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

int		ft_chem(t_set *set)
{
	int valid;
	int len_arg;
	
	len_arg = 0;
	while (set->arg[len_arg])
		len_arg++;

/* 
	 int x = -1;
	while (set->arg[++x])
		printf("[%s]\n", set->arg[x]);
	printf("[%s]\n", set->arg[x]);
		 */
		
	if (set->arg[0] != NULL)
		valid = chdir(set->arg[0]);
	//printf("[%s][%d]\n", set->arg[0], valid, len_arg);
	if (valid == -1 && set->arg[0] != NULL)
	{
		if (ft_strlen(set->arg[0]) == 0)
			return (-4);
		printf("minishell: cd: %s: No such file or directory\n", set->arg[0]);
	}
	if (set->arg[0] == NULL)
		return (chdir(ft_getenv()));
    return (0);
}

char *parc_env(t_set *set) //trouve PWD dans env et le copie
{
	int x;
	while (set->envp[x])
	{
		if (ft_strncmp(set->envp[x], "PWD=", 4) == 0)
		{
			//printf("pwd = [%s]\n", set->envp[x] + 4);
			return (ft_strdup(set->envp[x] + 4));
		}
		x++;
	}
	return (ft_strdup(""));
}

int ft_cd(t_set *set)
{
	char	buff[4096 + 1];
	int ret;
	char *temp;


	set->pwd = parc_env(set);
	
	ret = ft_chem(set); // cd
	//if (ret != -4)
	//{
		temp = ft_strdup(set->pwd);
		set->old_pwd = ft_strjoin("OLDPWD=", temp);
		ft_hideenv(set->old_pwd, set);
		ft_modenv(set->old_pwd, set);
		
		free(temp);
		free(set->old_pwd);
	//}
	//else
		//ret = 0;
	free(set->pwd);
	set->pwd = ft_strdup(getcwd(buff, 4097));
	temp = ft_strdup(set->pwd);
	free(set->pwd);

	set->pwd = ft_strjoin("PWD=", temp);
	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);

	free(temp);
	free(set->pwd);
	return (ret);
}