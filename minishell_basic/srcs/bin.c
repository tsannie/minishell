/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/17 16:47:10 by phbarrad         ###   ########.fr       */
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
	//printf("op = [%s]\n cmd + len[%s]\n", op,cmd + len);
	if (op == NULL)
		return (NULL);
	//printf("pt = [%s][%s]\n", path, cmd);
/* 	if (path != NULL)
	{
		if (path[r] == '.' && path[r + 1] == '/')
			r = 1;
	} */
	//printf("cmd + len = [%s]path =[%s]\n open(cmd) = [%s]\nop = [%s]\n", cmd + len, path, cmd, op);
	folder = opendir(op);
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
	if (path != NULL)
	{
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
	}
	set->pathbc = ft_strdup(cmd);
	return (set->pathbc);
	//return (cmd);
}

char				*get_path(t_set *set, char *path, char *cmd)
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
	set->pathbc = ft_strdup(path);
	return (ft_strjoin(path, cmd));
}

int					check_stat_file(t_set *set, char *path, char *cmd)
{
    struct stat fileStat;

	//printf("check_sta\n");
	//printf("sp[%s]p[%s]\n", set->path, path);
	//if (path != NULL)
	//	return (0);
	if (set->path != NULL)
	{
		//printf("set->pth = null\n");
		return (1);
	}
	//else if (ft_strlen(set->str) == 0)
	//	return (1);
	if (is_dir(cmd) == 1)
		return (1);
    if(stat(cmd, &fileStat) < 0)    
        return (1);
 
/*     printf("Information for %s\n", cmd);
    printf("---------------------------\n");
    printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    printf("Number of Links: \t%d\n",fileStat.st_nlink);
    printf("File inode: \t\t%d\n",fileStat.st_ino);
 
    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n"); */
	return (0);
 
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
	//printf("ici5\n");
	r = 0;
	//printf("\n\nexe[%s]\tcmd[%s]\n", path, cmd);
	//printf("stat = [%d] lstat = [%d]\n", stat(cmd), lstat(cmd));
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
/* 	else if (ret == 0)
	{
		set->exit_val = 5;
		ft_putstr_not_found(cmd, set);
		exit (set->exit_val);
	} */
	//printf("pid [%d]ret [%d]ex[%d]\n", pid , ret, set->exit_val);
	if (g == 1)
	{
		if (set->pathbc != NULL)
		{
			free(set->pathbc);
			set->pathbc = NULL;
		}
		if (ttm)
			free(ttm);
		//get_lastcmd(set);	
	}
	r = -1;
	//printf("ici6\n");
	while (args[++r])
		free(args[r]);
	free(args);
	return (0);
}

int					ft_strlenbc(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '/' && i > 0)
		i--;
	if (i > 0)
		return (i + 1);
	return (0);
}

char 					*cmd_in_pwd(t_set *set, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;
	char 			*tmp;

	folder = opendir(set->pwd + 4);
	//printf("fofo = [%d]tmp = [%s]\n", folder, set->pwd + 4);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
		{
			//printf("[%s]=====[%s]\n", item->d_name, cmd);
			closedir(folder);
			return (joinf(set->pwd + 4, "/", cmd, ""));
		}
	}
	return (NULL);
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

	//printf("e[%s]\npc[%s]\n", set->path, set->pathbc);
	//if (set->path == NULL)
	//	return (1);
	if (cmd[x] == '.' && cmd[x + 1] == '/')
	{
		chemin = 1;
		len = 2;
		path = ft_strdup("./");
	}
	//printf("ici1\n");
	while (cmd[x] == '.' && cmd[x + 1] == '.' && cmd[x + 2] == '/' && len == 0)
		x += 3;
	if (x != 0)
		x--;

		//	printf("ici2\n");

	while (cmd[x] && len == 0 && set->all_path)
	{
		while (set->all_path[y] && len == 0)
		{
			if (ft_strncmp(set->all_path[y], cmd + x,
			ft_strlen(set->all_path[y])) == 0 && path == NULL)
			{
				chemin = 1;
				len = x + ft_strlen(set->all_path[y]);
				path = ft_strdup(set->all_path[y]);
				//printf("chemin[%d] len[%d] path[%s]\n", chemin, len, path);
			}
			//printf("----p[%s]cmd[%s]alp + r[%s]====[%s]-+--\n",path,cmd + x, set->all_path[y] + r, set->all_path[y]); 	 
			y++;
		}
		//r = 0;
		y = 0;
		x++;
	}
	//printf("ici3\n");
	//printf("chemin = [%d]", chemin);
	//printf("chemin = [%d] path[%s] cmd[%s] r = [%d]\n", chemin, path, cmd, r);
	y = -1;
	if (chemin == 0 && path == NULL && set->all_path)
	{
		while (set->all_path[++y] && path == NULL)
		{
			path = get_path(set, set->all_path[y],cmd);
			//printf("oo[%s][%s]oo\n", path, set->all_path[y]);
		}
	}
	else if (chemin == 1)
	{
		//printf("ici44\n");
		path = get_path_chemin(set, path, len, cmd);
		//printf("g_p_c = [%s]p[%s]\n", cmd, path);
	}
	if (chemin == 0 && path == NULL)
	{
		//printf("path = [%s] len[%d] cmd[%s}\n", path, len, cmd);
		path = get_path_chemin(set, path, ft_strlenbc(cmd), cmd);
	}
	if (path == NULL && set->pwd != NULL)
	{
		path = cmd_in_pwd(set, cmd);
		len = ft_strlen(set->pwd);
	}
	if (path == NULL)
		return (1);
	//printf("ici4\n");


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
	if (check_stat_file(set, path, cmd) == 1)
	{
		//printf("check_stat = 1, set->path[%s]\n", set->path);
		return (1);
	}
	return (exec_bin(set, path, cmd));
}
