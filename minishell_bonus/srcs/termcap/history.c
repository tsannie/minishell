/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:55:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int				add_exist(t_set *set, int fd)
{
	char		*str;
	char		buff;
	int			i;

	str = ft_strdup("");
	i = 0;
	while (read(fd, &buff, 1) != 0)
	{
		if (buff != '\n')
			str = add_letter(str, buff);
		else if (buff == '\n')
		{
			set->history = addword(set->history, i + 1, str);
			ffree(str);
			set->inc_his++;
			str = ft_strdup("");
			i++;
		}
	}
	set->his_pos = set->inc_his;
	ffree(str);
	return (i);
}

void			init_his(t_set *set)
{
	char		*path;
	int			fd;
	int			i;

	path = joinf(set->pwd + 4, "/", ".minishell_history", "");
	fd = open(path, O_RDONLY);
	i = 0;
	if (fd >= 0)
	{
		i = add_exist(set, fd);
		close(fd);
		set->his_pos = i;
	}
	ffree(path);
}

void			add_in_his_file(t_set *set)
{
	char		*path;
	int			fd;
	int			i;

	path = joinf(set->pwd + 4, "/", ".minishell_history", "");
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IWUSR | S_IRUSR);
	i = 0;
	if (fd > 0)
	{
		ft_putstr_fd(set->str, fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	close(fd);
	ffree(path);
}

void			add_history(t_set *set)
{
	int m;

	m = 0;
	if (set->str != NULL)
	{
		if (ft_strlen(set->str) > 0)
		{
			if (set->inc_his == 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
				m = 1;
			}
			else if (ft_strcmp(set->history[set->inc_his - 1], set->str) != 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
				m = 1;
			}
		}
	}
	set->his_pos = set->inc_his;
	if (m == 1)
		add_in_his_file(set);
}
