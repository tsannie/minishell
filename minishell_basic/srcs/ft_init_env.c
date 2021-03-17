/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:24:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/17 10:36:29 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char **ft_strdup_tabl(char **envp)
{
	char **hide_envp;
	int y;
	int len;

	len = 0;
	y = 0;
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
/*  	int x = -1;
	while (envp[++x])
		printf("{%s}\n", envp[x]);
	printf("1\n\n");
	x = -1;
	while (hide_envp[++x])
		printf("[%s]\n", hide_envp[x]);
	printf("2\n\n");  */
	return (hide_envp);
}

int ft_menv(char *str, t_set *set)
{
	char *tmp;
    int i;
	int r;
	int j;

    i = 0;
    r = 0;
    j = 0;
    while (set->envp[i] != NULL)
	    i++;
	//free(set->envp[i]);
    //set->envp[i] = ft_strdup(str);
	//set->envp[i + 1] = malloc(sizeof(char) * 1);
    //set->envp[i + 1] = NULL;
	set->envp = addword(set->envp, i + 1, set, str);

/*   	 i = 0;
	while (set->envp[i] != NULL)
    {
		printf("menv = [%s]\n",set->envp[i]);
	    i++;
	} */
	//printf("\n\n\n");
    return (0);
}

char	*joinf(char *s1, char *s2, char *s3, char *s4)
{
	char	*res;
	int		globalsize;
	int		i;
	int		e;

	globalsize = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
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
	//printf("[{%s}]\n", res);
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

 	while (ft_strncmp("PATH=", envp[i], 5) != 0 && envp[i + 1])
	{
		//printf("envp = [%s]\n", envp[i]);
		i++;
	}
	//printf("envp = [%s]\n", envp[i]); 
	if (envp[i + 1] == NULL && ft_strncmp("PATH=", envp[i], 5) != 0)
	{
		//printf("NULLICI [%d] [%s]\n",ft_strncmp("PATH=", envp[i], 5) != 0, envp[i]);
		return (NULL);
	}
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

char	*change_slash(char *str)
{
	int			i;
	char		*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\\')
			res = add_letter(res, '\\');
		res = add_letter(res, str[i]);
		i++;
	}
	return (res);
}

char **ft_strdup_dslash(char **envp)
{
	char **hide_envp;
	int y;
	int len;

	len = 0;
	y = 0;
	while (envp[len] != NULL)
		len++;
	if (!(hide_envp = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (envp[y])
	{
		hide_envp[y] = change_slash(envp[y]);  // double slash
		y++;
	}
	hide_envp[y] = NULL;
/*  	int x = -1;
	while (envp[++x])
		printf("{%s}\n", envp[x]);
	printf("1\n\n");
	x = -1;
	while (hide_envp[++x])
		printf("[%s]\n", hide_envp[x]);
	printf("2\n\n");  */
	return (hide_envp);
}

void  ft_init_env(t_set *set, char **envp, char **av)
{
	int i;
	int j;
	int shlvl;
	int bar;
	int pwd;
	char *tmp;
	char buff[4096 + 1];

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
	//tmp = set->envp[0];
	//set->envp[0] = set->envp[1];
	//set->envp[1] = tmp;
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
	//printf("[%d][%d][%d]\n", pwd, shlvl, bar);
 	if (pwd == 0)
		ft_menv(joinf("PWD=", set->pwd, "", ""), set);
	if (shlvl == 0)
		ft_menv(joinf("SHLVL=", set->shlvl, "", ""), set);
	set->hide_envp = ft_strdup_dslash(set->envp);
	//if (bar == 0)
	//	ft_menv(joinf("_=", set->path, "/", set->lastcmd), set);
}