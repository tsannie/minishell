/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:24:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/17 16:04:04 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char **ft_strdup_tabl(char **envp)
{
	char **hide_envp;
	int x;
	int y;
	int len;

	len = 0;
	y = 0;
	x = 0;
	while (envp[len] != NULL)
		len++;
	if (!(hide_envp = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (envp[y])
	{
		hide_envp[y] = ft_strdup(envp[y]);
		y++;
	}
	hide_envp[y] = NULL;
	return (hide_envp);
}

int ft_menv(char *str, t_set *set)
{
    int i;
    
    i = 0;
    int r = 0;
    int j = 0;
	char *tmp;


    while (set->envp[i] != NULL)
	    i++;
	free(set->envp[i]);
    set->envp[i] = ft_strdup(str);
	set->envp[i + 1] = malloc(sizeof(char) * 1);
    set->envp[i + 1] = NULL;

/* 	 i = 0;
	while (set->envp[i] != NULL)
    {
		printf("[%s]\n",set->envp[i]);
	    i++;
	}
	printf("\n\n\n");  */
    return (0);
}

char	*joinf(char *s1, char *s2, char *s3, char *s4)
{
	char	*res;
	int		globalsize;
	int		i;
	int		e;

	globalsize = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(res = malloc(sizeof(char) * globalsize + 1)))
		return (NULL);
	i = 0;
	e = 0;
	while (s1[i])
		res[i++] = s1[e++];
	e = 0;
	while (s2[e])
		res[i++] = s2[e++];
	e = 0;
	while (s3[e])
		res[i++] = s3[e++];
	e = 0;
	while (s4[e])
		res[i++] = s4[e++];
	res[i] = '\0';
	//printf("[%s]\n", res);
	return (res);
}

char *ft_get_path(char **envp)
{
	int i;
	char *str;
	int j;
	int e;

	e = 0;
	j = 0;
	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	while (envp[i][j] != '=' && envp[i][j])
		j++;
	j++;
	if (!(str = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1 - j))))
		return (NULL);
	while (envp[i][j])
	{
		str[e] = envp[i][j];
		j++;
		e++;
	}
	//printf("[{%s}]\n", str);
	return (str);
}

void  ft_init_env(t_set *set, char **envp, char **av)
{
	int i;
	int j;
	int shlvl;
	int bar;
	int pwd;
	char *tmp;

	shlvl = 0;
	bar = 0;
	pwd = 0;
	j = -1;
	i = -1;
/* 	 int r = -1;
	while (envp[++r])
		printf("////[%s]\n", envp[r]);
	printf("\n\n\n\n\n"); 
 */
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	tmp = set->envp[0];
	set->envp[0] = set->envp[1];
	set->envp[1] = tmp;
/* 	 r = -1;
	while (set->envp[++r])
		printf("/[%s]\n", set->envp[r]);
	printf("\n\n\n\n\n");  */
	while (set->envp[++i])
	{
		if (ft_strncmp("SHLVL=", set->envp[i], 6) == 0)
			shlvl = 1;
		if (ft_strncmp("_=", set->envp[i], 2) == 0)
			bar = 1;
		if (ft_strncmp("PWD=", set->envp[i], 4) == 0)
			pwd = 1;
	} 
 	if (pwd == 0)
		ft_menv(joinf("PWD=", set->pwd, "", ""), set);
 	if (shlvl == 0)
		ft_menv("SHLVL=1", set);
	set->hide_envp = ft_strdup_tabl(set->envp);
	if (bar == 0)
		ft_menv(joinf("_=", set->path,"/", ""), set);
}