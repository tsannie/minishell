/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/22 16:27:17 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int			ft_strcmpsl(char *s1, char *s2)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	if (s1[len - 1] == '/')
		len--;
	while (s1[i] == s2[i] && s1[i] && i < len)
		i++;
	return (s1[i] - s2[i]);
}


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
		if (ft_strcmpsl(item->d_name, cmd + len) == 0)
			valid = 1;
		//printf("[%s]=====[%s]\n", item->d_name, cmd + len);
	}
	//printf("valid2 = [%d]path = [%s]\n", valid, path);
	closedir(folder);
	//printf("is_dir = [%d]\n",  is_dir(op));
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/", ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		//printf("cmd = [%s]\n", cmd);
		set->exit_val = 3;
		return (NULL);
	}
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
	set->pathbc = ft_strdup(set->cmd);
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
	//printf("valid = [%d]\n", valid);
	//printf("is_dir = [%d]\n\n", is_dir(cmd));
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/", ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		//printf("cmd = [%s]\n", cmd);
		set->exit_val = 3;
		return (NULL);
	}
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
	return (ft_strjoin(path, set->cmd));
}

int					check_stat_file(t_set *set, char *path, char *cmd)
{
    struct stat fileStat;
	int r;
	int w;
	int x;
	int d;
	int st;


	//printf("check_sta\n");
	//printf("sp[%s]p[%s]\n", set->path, path);
	//if (path != NULL)
	//	return (0);
/* 	if (set->path != NULL)
	{
		printf("set->pth != null\n");
		return (1);
	} */
	//else if (ft_strlen(set->str) == 0)
	//	return (1);
	///if (is_dir(cmd) == 1)
	//	return (1);
	st = stat(path, &fileStat);
	//printf("st = [%d]\n", st);    
        //return (0);
   // printf("Information for %s\n", path);
    //printf("---------------------------\n");
  	r = (fileStat.st_mode & S_IRUSR);
	w = (fileStat.st_mode & S_IWUSR);
    x = (fileStat.st_mode & S_IXUSR);
	d = (S_ISDIR(fileStat.st_mode));
/*      printf("r[%d]", r);
    printf("w[%d]", w);
    printf("x[%d]\n", x);
    printf("d[%d]\n", d);  
    printf("exit[%d]\n", set->exit_val);   */

	if (x == 0 && d != 0)
	{
		if (set->exit_val != 4)
			set->exit_val = 3;
		return (1);
	}
 	if (x == 0)
	{
		set->exit_val = 5;
		return (1);
	}
	if (x != 0 && w == 0 && r == 0)
	{
		set->exit_val = 5;
		return (1);
	}
	if (x != 0 && r == 0 && w != 0)
	{
		set->exit_val = 5;
		return (1);
	}
   // printf("File Size: \t\t%d bytes\n",fileStat.st_size);
   // printf("Number of Links: \t%d\n",fileStat.st_nlink);
   // printf("File inode: \t\t%d\n",fileStat.st_ino);

   // printf("File Permissions: \t");
/*     printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
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

int					check_sh(t_set *set, char *path)
{
	int i;
	int pwd;
	int sh;
	int len;


	len = ft_strlen(path);
	pwd = 0;
	sh = 0;
	i = 0;
	if (ft_strncmp(path, "./", 2) == 0)
		pwd = 1;
	if (ft_strncmp(path + len - 3, ".sh", ft_strlen(path + len - 3)) == 0)
		sh = 1;
	//printf("[%d][%d][%s][%d]\n", pwd, sh, path + len - 3,ft_strlen(path + len - 3));
	if (pwd == 1 && sh == 1)
	{
		//printf("sh.sh./\n");
		set->exit_val = 5;
		set->bleu = 1;
		return (1);
	}
	return (0);
}

int					exec_bin(t_set *set, char *path, char *cmd)
{
	int				pid;
	char			**args;
	int				r;
	char			*ttm;
	int 			g;
	int 			ret;

/* 	int x = -1;
	while (set->arg[++x])
		printf("1args = [%s]\n", set->arg[x]);
	printf("1cmd = [%s]\n\n", cmd);
	 */
	if (check_sh(set, path) == 1)
		return (1);


	pid = fork();
	args = new_args(set->arg, set, cmd);
	ret = 0;
	g = 0;
	r = 0;

	//printf("ici[%s]\n", path);	

/* 	x = -1;
	while (args[++x])
		printf("2args = [%s]\n", args[x]);
	printf("2cmd = [%s]\n\n", cmd); */
	if (path != NULL && pid == 0)
	{
 	/* 	int x = -1;
		while (args[++x])
			printf("args[%s]\n", args[x]); */
		/* x = -1;
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
			execve(path, args, set->envp);
		}
		else
			execve(path, args, set->envp);
		//ret = 32256;
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
	if (set->exit_val == 1)
		set->bleu = 1;
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
			return (joinf(set->pwd + 4, "/", set->cmd, ""));
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
			path = get_path(set, set->all_path[y],cmd);
	}
	else if (chemin == 1)
		path = get_path_chemin(set, path, len, cmd);
	if (chemin == 0 && path == NULL)
		path = get_path_chemin(set, path, ft_strlenbc(cmd), cmd);
	if (path == NULL && set->pwd != NULL && set->path == NULL)
	{
		path = cmd_in_pwd(set, cmd);
		if (is_dir(cmd) == 1)
		{
			set->bleu = 1;
			return (1);
		}
	}
	if (path == NULL)
		{
			set->bleu = 1;
			return (1);
		}
	//printf("set->path[%s]\npath = [%s]\n cmd = [%s]\n", set->path, path, cmd);
	if (check_stat_file(set, path, cmd) == 1)
	{
		set->bleu = 1;
		return (1);
	}
	return (exec_bin(set, path, cmd));
}
