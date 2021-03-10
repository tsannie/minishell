/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/10 16:26:07 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char				**new_args(char **args, t_set *set)
{
	char			**str;
	int				x;

	x = 0;
	while (args[x])
		x++;
	if (!(str = malloc(sizeof(char *) * (x + 2))))
		return (NULL);
	x = 0;
	str[x] = ft_strdup(set->cmd);
	while (args[x])
	{
		str[x + 1] = ft_strdup(args[x]);
		x++;
	}
	str[x + 1] = NULL;
	return (str);
}

char				*get_path_usr(t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	int				valid;

	valid = 0;
	folder = opendir("/usr/bin/");
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, set->cmd) == 0)
			valid = 1;
	}
	closedir(folder);
	if (valid == 0)
		return (NULL);
	return (ft_strjoin("/usr/bin/", set->cmd));
}

char				*get_path(t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	int				valid;

	valid = 0;
	folder = opendir("/bin/");
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, set->cmd) == 0)
			valid = 1;
	}
	closedir(folder);
	if (ft_strncmp(set->cmd, "./", 2) == 0 ||
	ft_strncmp(set->cmd, "../", 3) == 0)
		return ft_strdup(set->cmd);
	if (valid == 0)
		return (NULL);
	return (ft_strjoin("/bin/", set->cmd));
}

char				*ee_dir(t_set *set, char *path, int len)
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
		if (ft_strcmp(item->d_name, set->cmd + len) == 0)
			valid = 1;
	}
	closedir(folder);
	if (valid == 0)
		return (NULL);
	return (ft_strjoin(path, set->cmd + len));
}

char				*get_path_chemin(t_set *set, int len)
{
	char			*path;
	int				i;

	i = 0;
	if (!(path = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (set->cmd[i] && ft_strncmp(set->cmd + i,
	set->cmd + len, ft_strlen(set->cmd + len)))
	{
		path[i] = set->cmd[i];
		i++;
	}
	path[i] = '\0';
	return(ee_dir(set, path, len));
}

int					exec_bin(t_set *set, char *path)
{
	int				pid;
	char			**args;
	int				r;

	pid = fork();
	args = new_args(set->arg, set);
	int ret = 0;
	r = 0;
		//printf("exit = [%d]\n", set->exit_val);
	if (path != NULL && pid == 0)
	{
/* 		int x = -1;
		while (args[++x])
			printf("args[%s]\n", args[x]);
		x = -1;
		while (set->envp[++x])
			printf("args[%s]\n", set->envp[x]);
		printf("[%s]\n", path);	 */
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
	//printf("pid [%d]ret [%d]ex[%d]\n", pid , ret, set->exit_val);
	r = -1;
	while (args[++r])
		free(args[r]);
	free(args);
	return (0);
}

int					bash_cmd(t_set *set)
{
	char			*path;
	int				x;
	int				len;
	int				chemin;

	x = 0;
	len = 0;
	chemin = 0;
	while (set->cmd[x])
	{
		if (ft_strncmp("/bin/", set->cmd + x, 5) == 0)
			chemin = 1;
		if (ft_strncmp("/usr/bin/", set->cmd + x, 9) == 0)
			chemin = 2;
		if (chemin == 0)
			len++;
		x++;
	}
	//printf("[%d]\n", chemin);
	if (chemin == 0)
		path = get_path(set);
	else if (chemin == 1)
		path = get_path_chemin(set, len + 5);
	else if (chemin == 2)
		path = get_path_usr(set);
	if (path == NULL)
		return (1);
	//printf("path = [%s]\n", path);
	return (exec_bin(set, path));
}
