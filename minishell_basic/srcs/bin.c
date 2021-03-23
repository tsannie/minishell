/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 17:48:10 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

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
	if (path == NULL)
	{
		set->bleu = 1;
		return (1);
	}
	if (check_stat_file(set, path, cmd) == 1)
	{
		set->bleu = 1;
		return (1);
	}
	return (exec_bin(set, path, cmd));

}

int					bash_cmd(t_set *set, char *cmd)
{
	char			*path;
	int				x;
	int				y;
	int				chemin;

	y = 0;
	x = 0;
	set->len = 0;
	chemin = 0;
	path = NULL;
	if (cmd[x] == '.' && cmd[x + 1] == '/')
	{
		chemin = 1;
		set->len = 2;
		path = ft_strdup("./");
	}
	while (cmd[x] == '.' && cmd[x + 1] == '.' && cmd[x + 2] == '/' && set->len == 0)
		x += 3;
	if (x != 0)
		x--;
	while (cmd[x] && set->len == 0 && set->all_path)
	{
		while (set->all_path[y] && set->len == 0)
		{
			if (ft_strncmp(set->all_path[y], cmd + x,
			ft_strlen(set->all_path[y])) == 0 && path == NULL)
			{
				chemin = 1;
				set->len = x + ft_strlen(set->all_path[y]);
				path = ft_strdup(set->all_path[y]);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (chemin_path(chemin, path, set, cmd));
}
