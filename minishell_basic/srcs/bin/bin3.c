/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:27:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/01 16:45:11 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

char				*cmd_in_pwd(t_set *set, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(set->pwd + 4);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
		{
			closedir(folder);
			return (joinf(set->pwd + 4, "/", set->cmd, ""));
		}
	}
	closedir(folder);
	return (NULL);
}

int					pathnnul(int valid, char *path, char *cmd, t_set *set)
{
	if (valid == 1 && ft_strncmp(path, "./", ft_strlen(path)) == 0
	&& is_dir(cmd + set->lene) == 1)
	{
		set->exit_val = 3;
		return (1);
	}
	if ((valid == 0) || (valid == 0 && ft_strncmp(path, "./",
	ft_strlen(path)) == 0))
	{
		set->exit_val = 4;
		return (1);
	}
	return (0);
}

int					end_exec(t_set *set, int ret, char *path)
{
	if (ret == 256)
		set->exit_val = 1;
	else if (ret == 54784)
		set->exit_val = 1;
	if (set->exit_val == 1)
		set->bleu = 1;
	if (set->g == 1)
		ffree(set->pathbc);
	if (path != NULL)
		free(path);
	return (0);
}

void				ff_env(t_set *set, char *cmd, char *path)
{
	char			*ttm;

	ttm = NULL;
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
	{
		ttm = ft_strjoin("_=", path);
		ft_modenv(ttm, set);
		set->g = 1;
		free(ttm);
	}
}

int					exec_bin(t_set *set, char *path, char *cmd)
{
	char			**args;
	int				ret;
	int				pid;

	if (check_sh(set, path) == 1)
		return (1);
	pid = fork();
	args = new_args(set->arg, cmd);
	ret = 0;
	if (path != NULL && pid == 0)
	{
		ff_env(set, cmd, path);
		execve(path, args, set->envp);
	}
	else
		waitpid(pid, &ret, 0);
	ft_free_dbtab(args);
	return (end_exec(set, ret, path));
}
