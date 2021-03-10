/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/10 13:36:10 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char				**new_args(char **args)
{
	char			**str;
	int				x;

	x = 0;
	while (args[x])
		x++;
	if (!(str = malloc(sizeof(char *) * (x + 2))))
		return (NULL);
	x = 0;
	str[x] = ft_strdup("");
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
	args = new_args(set->arg);
	r = 0;
	if (path != NULL && pid == 0)
	{
		set->exit_val = execve(path, args, set->envp);
		r = -1;
		while (args[++r])
			free(args[r]);
		free(args);
		free(path);
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
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
	if (chemin == 0)
		path = get_path(set);
	else 
		path = get_path_chemin(set, len + 5);
	if (path == NULL)
		path = get_path_usr(set);
	if (path == NULL)
		return (1);
	return (exec_bin(set, path));
}
