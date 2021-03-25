/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:27:25 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 16:28:12 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char				*cmd_in_pwd(t_set *set, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;
	// y'avait valid donc ca rentrait pas dans le while la

	folder = opendir(set->pwd + 4);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))		// condition de valid =0 degage car valid non init
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
	char			*op;

	valid = 0;
	op = ft_strdupbc(cmd);

	//printf("p[%s]c[%s]op=[%s]\n", path, cmd, op);
	//printf("-=-=-1\n");
	if (op == NULL)
	{
		if (ft_strlen(op) == 1)
			return (NULL);
	//printf("p[%s]c[%s]valid[%d]\n", path, cmd, valid);
		return (NULL);
	}
	folder = opendir(op);
	if (!folder)
	{
		free(op);
		//printf("path[%s]\ncmd[%s]\nvalid[%d]\nop[%s]\nis[%d]\n",
		//path, cmd, valid, op, is_dir_presentsl(path, cmd + ft_strlen(path)));
		//printf("fail folder\n");
		if (path != NULL && is_dir_presentsl(path, cmd + ft_strlen(path)) == 1)
			set->exit_val = 7;
		//set->bleu = 1;
		return (NULL);
	}
	free(op);
	while ((item = readdir(folder)) && valid == 0)
	{
		if (ft_strcmpsl(item->d_name, cmd + len) == 0)
		{
			//printf("----------[%s][%s]valid[%d]\n", item->d_name, cmd + len, valid);
			valid = 1;
		}
	}
	closedir(folder);
	//printf("p[%s]c[%s]valid[%d]\n", path, cmd, valid);
//	printf("valid [%d][%d][%s]\n", valid, is_dir(cmd), cmd);
	if (valid == 0 && is_dir(cmd) == 1 &&
	ft_strncmp(cmd + ft_strlen(cmd) - 1, "/",
	ft_strlen(cmd + ft_strlen(cmd) - 1)) == 0)
	{
		set->exit_val = 3;
		return (NULL);
	}
	if (path != NULL)
	{
		//printf("path = null\n");
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
			//printf("ici\n");
			set->exit_val = 4;
			return (NULL);
		}
	}
	else if (valid == 1 && is_dir(cmd) == 1)
	{
		//printf("oui\n");
		set->exit_val = 3;
		return (NULL);
	}
	if (ft_strlen(op) <= 1 && is_dir(cmd) == 1)
	{
		//printf("IIC\n");
		set->exit_val = 3;
		return (NULL);
	}
	if (valid == 0 && is_dir(cmd) == 0)
	{
		set->exit_val = 6;
		return (NULL);
	}
	//printf("NON\n");
	//printf("valid [%d][%d][%s] len = [%d][%s]\n", valid, is_dir(cmd), cmd, ft_strlen(op), op);
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
