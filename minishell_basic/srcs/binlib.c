/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:28:38 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 15:32:22 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int					ft_strcmpss(char *s1, char *s2)
{
	int				i;

	i = 0;
	if (ft_strlen(s1) - 1 != ft_strlen(s2))
		return (1);
	while (s1[i] == s2[i] && s1[i] && s1[i + 1] != '/')
		i++;
	return (s1[i] - s2[i]);
}

int					ft_strcmpsl(char *s1, char *s2)
{
	int				i;
	int				len;

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

int					check_stat_file(t_set *set, char *path)
{
	struct stat		filestat;
	int				r;
	int				w;
	int				x;
	int				d;
	int				st;

	st = stat(path, &filestat);		// pas utilise
	(void)st;
	r = (filestat.st_mode & S_IRUSR);
	w = (filestat.st_mode & S_IWUSR);
	x = (filestat.st_mode & S_IXUSR);
	d = (S_ISDIR(filestat.st_mode));
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
	return (0);
}

int					check_sh(t_set *set, char *path)
{
	int				pwd;
	int				sh;
	int				len;

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