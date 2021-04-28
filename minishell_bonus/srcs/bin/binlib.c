/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:28:38 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char				**new_args(char **args, char *cmd)
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

int					checkmode(t_set *set)
{
	if (set->x == 0 && set->d != 0)
	{
		if (set->exit_val != 4)
			set->exit_val = 3;
		return (1);
	}
	if (set->x == 0)
	{
		set->exit_val = 5;
		return (1);
	}
	if (set->x != 0 && set->w == 0 && set->r == 0)
	{
		set->exit_val = 5;
		return (1);
	}
	if (set->x != 0 && set->r == 0 && set->w != 0)
	{
		set->exit_val = 5;
		return (1);
	}
	return (0);
}

int					check_stat_file(t_set *set, char *path)
{
	struct stat		filestat;
	int				st;

	st = stat(path, &filestat);
	(void)st;
	set->r = (filestat.st_mode & S_IRUSR);
	set->w = (filestat.st_mode & S_IWUSR);
	set->x = (filestat.st_mode & S_IXUSR);
	set->d = (S_ISDIR(filestat.st_mode));
	if (checkmode(set) == 1)
		return (1);
	return (0);
}

int					check_sh(t_set *set, char *path)
{
	int				pwd;
	int				sh;
	int				len;

	set->g = 0;
	len = ft_strlen(path);
	pwd = 0;
	sh = 0;
	if (ft_strncmp(path, "./", 2) == 0)
		pwd = 1;
	if (ft_strncmp(path + len - 3, ".sh", ft_strlen(path + len - 3)) == 0)
		sh = 1;
	if (pwd == 1 && sh == 1)
	{
		set->exit_val = 5;
		set->bleu = 1;
		return (1);
	}
	return (0);
}

int					ft_strlenbc(char *str)
{
	int				i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '/' && i > 0)
		i--;
	if (i > 0)
		return (i + 1);
	return (0);
}
