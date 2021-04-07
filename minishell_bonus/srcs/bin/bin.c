/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int					fot(t_set *set, char *path, char *cmd)
{
	if (path == NULL)
	{
		set->bleu = 1;
		return (1);
	}
	else if (check_stat_file(set, path) == 1)
	{
		set->bleu = 1;
		return (1);
	}
	return (exec_bin(set, path, cmd));
}

int					chemin_path(int chemin, char *path, t_set *set, char *cmd)
{
	int				y;

	y = -1;
	if (chemin == 0 && path == NULL && set->all_path)
	{
		while (set->all_path[++y] && path == NULL)
			path = get_path(set, set->all_path[y], cmd);
	}
	else if (chemin == 1)
		path = get_path_chemin(set, path, set->len, cmd);
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
	return (fot(set, path, set->cmd));
}

int					setx(t_set *set, char *cmd)
{
	int x;

	x = 0;
	while (cmd[x] == '.' && cmd[x + 1] == '.' && cmd[x + 2] == '/'
	&& set->len == 0)
		x += 3;
	if (x != 0)
		x--;
	return (x);
}

char				*iffexec(t_set *set, char *cmd)
{
	char *path;

	path = NULL;
	set->len = 0;
	set->chemin = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		set->chemin = 1;
		set->len = 2;
		path = ft_strdup("./");
	}
	return (path);
}

int					bash_cmd(t_set *set)
{
	char			*path;
	char			*cmd;
	int				x;
	int				y;

	y = -1;
	cmd = maj_to_min(set->cmd);
	path = iffexec(set, cmd);
	x = setx(set, cmd);
	while (cmd[x] && set->len == 0 && set->all_path && path == NULL)
	{
		while (set->all_path[++y] && set->len == 0)
		{
			if (ft_strncmp(set->all_path[y], cmd + x,
			ft_strlen(set->all_path[y])) == 0 && path == NULL)
			{
				set->chemin = 1;
				set->len = x + ft_strlen(set->all_path[y]);
				path = ft_strdup(set->all_path[y]);
			}
		}
		y = -1;
		x++;
	}
	return (finn(set, path, cmd));
}
