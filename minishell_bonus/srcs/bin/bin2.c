/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:27:25 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/11 08:49:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int					check_elem_chem(char *cmd, int valid, char *path,
t_set *set)
{
	if (valid == 0 && is_dir(cmd) == 1 && ft_strncmp(cmd + ft_strlen(cmd) - 1,
	"/", ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		set->exit_val = 3;
		return (1);
	}
	if (path != NULL)
	{
		if (pathnnul(valid, path, cmd, set) == 1)
			return (1);
	}
	else if ((valid == 1 && is_dir(cmd) == 1) || (is_dir(cmd) == 1))
	{
		set->exit_val = 3;
		return (1);
	}
	if (valid == 0 && is_dir(cmd) == 0)
	{
		set->exit_val = 6;
		return (1);
	}
	ffree(set->pathbc);
	set->pathbc = ft_strdup(set->cmd);
	return (0);
}

DIR					*init_folder(char *cmd, char *path, t_set *set)
{
	DIR				*folder;
	char			*op;

	op = ft_strdupbc(cmd);
	if (op == NULL)
	{
		if (ft_strlen(op) == 1)
			return (NULL);
		return (NULL);
	}
	folder = opendir(op);
	if (!folder)
	{
		free(op);
		if (path != NULL && is_dir_presentsl(path, cmd + ft_strlen(path)) == 1)
			set->exit_val = 7;
		return (NULL);
	}
	free(op);
	return (folder);
}

char				*get_path_chemin(t_set *set, char *path, int len, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;

	valid = 0;
	set->lene = len;
	folder = init_folder(cmd, path, set);
	if (folder == NULL)
		return (NULL);
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmpsl(item->d_name, cmd + len) == 0)
			valid = 1;
	}
	closedir(folder);
	if (check_elem_chem(cmd, valid, path, set) == 1)
		return (NULL);
	//if (ft_strncmp("./", path, len) != 0)
	//	ffree(path);	leak / segfault
	//ffree(path);
	return (ft_strdup(set->pathbc));
}

int					check_elem(char *cmd, int valid, char *path, t_set *set)
{
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/",
	ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		set->exit_val = 3;
		return (1);
	}
	if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0
	&& is_dir(cmd) == 1)
	{
		set->exit_val = 3;
		return (1);
	}
	if (valid == 0 && ft_strncmp(path, "./", ft_strlen(path)) == 0)
	{
		set->exit_val = 4;
		return (1);
	}
	if (valid == 0)
		return (1);
	return (0);
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
	}
	closedir(folder);
	if (check_elem(cmd, valid, path, set) == 1)
		return (NULL);
	ffree(set->pathbc);
	set->pathbc = ft_strdup(path);
	return (ft_strjoin(path, cmd));
}
