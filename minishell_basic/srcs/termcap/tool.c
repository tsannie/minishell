/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:29:50 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/26 14:47:33 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int				set_fle(t_set *set, char *buf)
{
	signal(SIGINT, SIG_IGN);
	if (buf[1] == 91)
	{
		if (buf[2] == 68)
			move_left(set);
		else if (buf[2] == 67)
			move_right(set);
		else if (buf[2] == 65)
			history_prev(set);
		else if (buf[2] == 66)
			history_next(set);
	}
	return (0);
}

char			*ft_strdup_free_len(char *str, int len)
{
	int			i;
	char		*new;

	i = 0;
	if (!str || len <= 0)
		return (ft_strdup(""));
	if (!(new = malloc(sizeof(char) * (len))))
		return (NULL);
	while (i < len - 1)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

int				ft_dell(t_set *set)
{
	size_t		col;
	size_t		len;

	len = ft_strlen(set->str);
	col = set->col;
	set->str = ft_strdup_free_len(set->str, len);
	if (len > 0)
	{
		ft_putstr_fd(set->tt_left, STDERR);
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
	}
	return (0);
}

void			all_ccmd(char *buf, t_set *set)
{
	if (buf[0] == 127 && ft_strlen(buf) == 1)
		buf[0] = ft_dell(set);
	else if (buf[0] == 9 && ft_strlen(buf) == 1)
		buf[0] = 0;
	else if (ft_strlen(buf) == 3 && buf[0] == 27)
	{
		set_fle(set, buf);
		buf[0] = 0;
		buf[1] = 0;
	}
	else if (ft_strlen(buf) == 1 && buf[0] == 4)
	{
		if (ft_strlen(set->str) == 0)
		{
			ft_putstr_fd("exit\n", STDERR);
			exit(0);
		}
	}
	else
		set->str = ft_strjoin_free(set->str, buf);
}

void			eeddn(t_set *set)
{
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str) - 1] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
}
