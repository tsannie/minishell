/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/12 14:28:24 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char				**new_args(char **args, t_set *set, char *cmd)
{
	char			**str;
	int				x;

	x = 0;
	while (args[x])
		x++;
	if (!(str = malloc(sizeof(char *) * (x + 2))))
		return (NULL);
	x = 0;
	str[x] = ft_strdup(cmd);
	while (args[x])
	{
		str[x + 1] = ft_strdup(args[x]);
		x++;
	}
	str[x + 1] = NULL;
	return (str);
}

char				*get_path_chemin(t_set *set, char *path, int len, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;
	
	valid = 0;
	folder = opendir(path);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd + len) == 0)
			valid = 1;
	}
	closedir(folder);
	if (valid == 0)
		return (NULL);
	set->pathbc = ft_strdup(path);
	return (ft_strjoin(path, cmd + len));
}

char				*get_path(t_set *set, char *path, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;

	valid = 0;
	//printf("pt = [%s]\n", path);
	folder = opendir(path);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
			valid = 1;
	//	printf("[%s][%s][%d]\n", item->d_name, cmd, ft_strcmp(item->d_name, cmd));
	}
	closedir(folder);
	if (ft_strncmp(cmd, "./", 2) == 0 ||
	ft_strncmp(cmd, "../", 3) == 0)
		return ft_strdup(cmd);
	if (valid == 0)
		return (NULL);
	set->pathbc = ft_strdup(path);
	return (ft_strjoin(path, cmd));
}

int					exec_bin(t_set *set, char *path, char *cmd)
{
	int				pid;
	char			**args;
	int				r;
	char			*ttm;
	int g = 0;
	pid = fork();
	args = new_args(set->arg, set, cmd);
	int ret = 0;

	r = 0;
		//printf("exit = [%d]\n", set->exit_val);
	if (path != NULL && pid == 0)
	{
/*  		int x = -1;
		while (args[++x])
			printf("args[%s]\n", args[x]);
		x = -1;
		while (set->envp[++x])
			printf("env[%s]\n", set->envp[x]);
		printf("path [%s]\n cmd = [%s]\n", path, cmd);	 */
		if (ft_strncmp(cmd, "env", ft_strlen(cmd) == 0) == 0)
		{
			ttm = joinf("_=", set->pathbc, set->cmd, "");
			ft_modenv(ttm, set);
			g = 1;
			set->exit_val = execve(path, args, set->envp);
		}
		else
			set->exit_val = execve(path, args, set->envp);
/*		r = -1;
		while (args[++r])
			free(args[r]);
		free(args);
		free(path);
		exit(0); */
	}
	else
		waitpid(pid, &ret, 0);
	if (ret == 256)
		set->exit_val = 1;
	else
		set->exit_val = 0;
	//printf("pid [%d]ret [%d]ex[%d]\n", pid , ret, set->exit_val);
	if (g == 1)
	{
		if (set->pathbc != NULL)
		{
			free(set->pathbc);
			set->pathbc = NULL;
		} 
		free(ttm);
		get_lastcmd(set);	
	}
	r = -1;
	while (args[++r])
		free(args[r]);
	free(args);
	return (0);
}

int					bash_cmd(t_set *set, char *cmd)
{
	char			*path;
	int				x;
	int				y;
	int				len;
	int				chemin;

	y = 0;
	x = 0;
	len = 0;
	chemin = 0;
	path = NULL;
	while (cmd[x])
	{
		while (set->all_path[y])
		{
			if (ft_strncmp(set->all_path[y], cmd + x,
			ft_strlen(set->all_path[y])) == 0)
			{
				chemin = 1;
				len = ft_strlen(set->all_path[y]);
				path = ft_strdup(set->all_path[y]);
			}	 	 
			y++;
		} 
		x++;
	}
	//printf("chemin = [%d]\n", chemin);
	y = -1;
	if (chemin == 0)
	{
		while (set->all_path[++y] && path == NULL)
		{
			path = get_path(set, set->all_path[y], cmd);
		}
	//	printf("act path = [%s]\n", path);
	}
	else if (chemin == 1)
		path = get_path_chemin(set, path, len, cmd);
	if (path == NULL)
		return (1);


/* 	char *ttm;
	ttm = joinf("_=", set->pathbc, set->cmd, "");
	ft_modenv(ttm, set);
	ft_hideenv(ttm, set);
 	if (set->pathbc != NULL)
	{
		free(set->pathbc);
		set->pathbc = NULL;
	} 
	free(ttm); */
	//printf("final path = [%s]\n", path);

	
	return (exec_bin(set, path, cmd));
}
