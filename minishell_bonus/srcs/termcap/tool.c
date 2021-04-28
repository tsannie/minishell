/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:29:50 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			go_home(t_set *set, char *buf)
{
	size_t len;

	len = ft_strlen(set->str);
	while (set->cur_pos > 12)
	{
		ft_putstr_fd(set->tt_left, STDERR);
		set->cur_pos--;
	}
}

void			go_end(t_set *set, char *buf)
{
	size_t len;

	len = ft_strlen(set->str);
	while (set->cur_pos < (ft_strlen(set->str) + 12))
	{
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
}

int				set_fle(t_set *set, char *buf)
{
	signal(SIGINT, SIG_IGN);
	if (buf[1] == 91)
	{
		if (buf[2] == 65)
			history_prev(set, buf);
		else if (buf[2] == 66)
			history_next(set, buf);
		else if (buf[2] == 70)
			go_home(set, buf);
		else if (buf[2] == 72)
			go_end(set, buf);
		else if (buf[2] == 67 && set->cur_pos < (ft_strlen(set->str) + 12))
		{
			set->cur_pos++;
			ft_putstr_fd(set->tt_right, STDERR);
		}
		else if (buf[2] == 68 && set->cur_pos > 12)
		{
			set->cur_pos--;
			ft_putstr_fd(set->tt_left, STDERR);
		}
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
	}
	return (0);
}

char			*ft_strdup_free_len(char *str, int len)
{
	int			i;
	char		*new;

	i = 0;
	if (!str || len <= 0)
	{
		ffree(str);
		return (ft_strdup(""));
	}
	if (!(new = malloc(sizeof(char) * (len))))
		return (NULL);
	while (i < len - 1)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	ffree(str);
	return (new);
}

int				ft_dell(t_set *set)
{
	size_t		len;
	size_t		col;

	col = set->col;
	len = ft_strlen(set->str);
	set->str = ft_strdup_free_len(set->str, len);
	set->dell_len = getdellen(len + 12, col);
	if ((len + 12) == col)
	{
		ft_putstr_fd(set->tt_up, STDERR);
		ft_putstr_fd("\033[2K", STDERR);
		disp_prompt();
		ft_putstr_fd(set->str, STDERR);
	}
	else if (((len + 12) % col) == 0 && ((len + 12) >= col * 2))
	{
		ft_putstr_fd(set->tt_up, STDERR);
		ft_putstr_fd("\033[2K", STDERR);
		ft_putstr_fd(set->str + ((col * set->dell_len) - 12), STDERR);
	}
	else if (len > 0)
		aff_dell(set);
	set->cur_pos--;
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
	}
	else if (ft_strlen(buf) == 1 && buf[0] == 4)
	{
		if (ft_strlen(set->str) == 0)
		{
			ft_putstr_fd("exit\n", STDERR);
			exit(0);
		}
		buf[0] = 0;
	}
	else if (buf[0] != 10)
	{
		set->str = ft_strjoin_free_len(set->str, buf, set->cur_pos - 12);
		set->cur_pos++;
	}
}

void			eeddn(t_set *set)
{
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str)] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
}
