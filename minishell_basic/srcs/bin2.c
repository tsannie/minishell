/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:27:25 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 17:30:14 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char				*cmd_in_pwd(t_set *set, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;
	char			*tmp;

	folder = opendir(set->pwd + 4);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
		{
			closedir(folder);
			return (joinf(set->pwd + 4, "/", set->cmd, ""));
		}
	}
	return (NULL);
}

char				*get_path_chemin(t_set *set, char *path, int len, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	int				valid;
	int				ap;
	int				r;
	char			*op;

	r = 0;
	valid = 0;
	op = ft_strduplen(cmd, len);
	if (op == NULL)
		return (NULL);
	folder = opendir(op);
	if (!folder)
	{
		free(op);
		return (NULL);
	}
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmpsl(item->d_name, cmd + len) == 0)
			valid = 1;
	}
	closedir(folder);
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/",
	ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		set->exit_val = 3;
		return (NULL);
	}
	if (path != NULL)
	{
		if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0
		&& is_dir(cmd + len) == 1)
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
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/",
	ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		set->exit_val = 3;
		return (NULL);
	}
	if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0
	&& is_dir(cmd) == 1)
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
