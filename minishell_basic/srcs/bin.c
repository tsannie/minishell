/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/16 16:18:24 by phbarrad         ###   ########.fr       */
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
	int 			ap;
	valid = 0;
	int r = 0;
	char *op;
	
/* 	if (ft_strncmp(cmd + len, ".", ft_strlen(cmd + len)) == 0 ||
	ft_strncmp(cmd + len, "..", ft_strlen(cmd + len)) == 0)
	{
		set->exit_val = 3;
		return (NULL);
	} */
	op = ft_strduplen(cmd, len);

	//printf("pt = [%s][%s]\n", path, cmd);
/* 	if (path != NULL)
	{
		if (path[r] == '.' && path[r + 1] == '/')
			r = 1;
	} */
	//printf("cmd + len = [%s]path =[%s]\n open(cmd) = [%s]\nop = [%s]\n", cmd + len, path, cmd, op);
	folder = opendir(op);
	free(op);
	//printf("folder = [%d]\n", ap);
	if (!folder)
	{
		free(op);
		return (NULL);
	}
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmp(item->d_name, cmd + len) == 0)
			valid = 1;
		//printf("[%s]=====[%s]\n", item->d_name, cmd + len);
	}
	//printf("valid = [%d]\n", valid);
	closedir(folder);
	//printf("is_dir = [%d]\n",  is_dir(op));
	if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0 && is_dir(cmd + len) == 1)
	{
		set->exit_val = 3;
		return (NULL);
	}
	if (valid == 0 && ft_strncmp(path, "./", ft_strlen(path)) == 0)
	{
		set->exit_val = 4;
		return (NULL);
	}
	if (valid == 0)
	{
		set->exit_val = 4;
		return (NULL);
	}
	set->pathbc = ft_strdup(cmd);
	return (set->pathbc);
	//return (cmd);
}

char				*get_path(t_set *set, char *path, int r, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;

	valid = 0;
	folder = opendir(path + r);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
			valid = 1;
		//printf("item[%s]==[%s]==[%d]\n", item->d_name, cmd, ft_strcmp(item->d_name, cmd));
	}
	closedir(folder);
	if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0 && is_dir(cmd) == 1)
	{
		set->exit_val = 3;
		return (NULL);
	}
	if (valid == 0 && ft_strncmp(path, "./", ft_strlen(path)) == 0)
	{
		set->exit_val = 4;
		return (NULL);
	}
	if (valid == 0)
		return (NULL);
	set->pathbc = ft_strdup(path + r);
	return (ft_strjoin(path + r, cmd));
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
	//printf("exe= [%s]\n", path);
	if (path != NULL && pid == 0)
	{
/*  		int x = -1;
		while (args[++x])
			printf("args[%s]\n", args[x]);
		x = -1;
		while (set->envp[++x])
			printf("env[%s]\n", set->envp[x]); */
		
		//printf("ici[%s]\n", path);	
		//printf("pathe [%s]\ncmd = [%s]\n", path, cmd);	
		if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0) //  ../../../../usr/bin/env
		{
			//printf("----------cmd = end-----------\n");
			ttm = joinf("_=", path, "", "");
			ft_modenv(ttm, set);
			//printf("\n\n----ENV----\n\n");
			//printf("ttm = [%s]\n", ttm);
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
	//printf("ret = [%d]\n", ret);
	if (ret == 256)
		set->exit_val = 1;
	else if (ret == 54784)
		set->exit_val = 1;
	if (set->exit_val != 1) //heuu jsp
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
		//get_lastcmd(set);	
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
	int r = 0;

	if (cmd[x] == '.' && cmd[x + 1] == '/')
	{
		chemin = 1;
		len = 2;
		path = ft_strdup("./");
	}
	while (cmd[x] == '.' && cmd[x + 1] == '.' && cmd[x + 2] == '/' && len == 0)
		x += 3;
	if (x != 0)
		x--;
	while (cmd[x] && len == 0)
	{
		while (set->all_path[y] && len == 0)
		{
			r = 0;
			//printf("oo[%s][%s][%s]oo\n", set->all_path[y] + r, cmd + x, path);
			if (ft_strncmp(set->all_path[y] + r, cmd + x,
			ft_strlen(set->all_path[y] + r)) == 0 && path == NULL)
			{
				chemin = 1;
				len = x + ft_strlen(set->all_path[y] + r);
				path = ft_strdup(set->all_path[y] + r);
				//printf("chemin[%d] len[%d] path[%s]\n", chemin, len, path);
			}
		//	printf("----p[%s]cmd[%s]alp[%s]-+--\n",path,cmd + x, set->all_path[y]); 	 
			y++;
		}
		//r = 0;
		y = 0;
		x++;
	}
	//printf("chemin = [%d] path[%s] cmd[%s] r = [%d]\n", chemin, path, cmd, r);
	y = -1;
	if (chemin == 0 && path == NULL)
	{
		while (set->all_path[++y] && path == NULL)
		{
			path = get_path(set, set->all_path[y], r,cmd);
			//printf("oo[%s][%s]oo\n", path, set->all_path[y]);
		}
	}
	else if (chemin == 1)
	{
		path = get_path_chemin(set, path, len, cmd);
		//printf("g_p_c = [%s]p[%s]\n", cmd, path);
	}
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

	//return (1);
	//if (ft_strncmp(cmd, "..", ft_strlen(cmd)) == 0)
	//	return (1);
	return (exec_bin(set, path, cmd));
}
