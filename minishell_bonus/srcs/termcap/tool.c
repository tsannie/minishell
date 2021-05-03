/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:29:50 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/29 16:59:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

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

char			*ft_strdup_free_pos(char *str, int len, int pos)
{
	int			i;
	char		*new;
	int e;

	e = 0;
	i = 0;
	if (!str || len <= 0)
	{
		ffree(str);
		return (ft_strdup(""));
	}
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (pos == i)
			e++;
		new[i] = str[i + e];
		i++;
	}
	new[i] = '\0';
	ffree(str);
	return (new);
}

void			dell_last_aff(int len, t_set *set)
{
	int len_cp;

	len_cp = set->cur_pos - 12;
	while (len_cp++ < len)
		ft_putstr_fd(set->tt_right, STDERR);
	//aff_dell(set);
	//while (len_cp-- >= set->cur_pos - 12)
	//	ft_putstr_fd(set->tt_left, STDERR);
}

int				ft_dell(t_set *set)
{
	size_t		len;
	size_t		col;


	col = set->col;
	len = ft_strlen(set->str);
	set->str = ft_strdup_free_pos(set->str, len, set->cur_pos - 13);
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

void 	free_buff(char *buf)
{
	if (buf[0] != 0)
	{
		ft_bzero((void *)buf, BUF_SIZE);
		buf[0] = 0;
	}
}

void			aff_modif_str(t_set *set, char *buf)
{
	size_t		len;
	int			pos;

	pos = set->cur_pos + 1;
	len = ft_strlen(set->str);
	set->str = ft_strjoin_free_len(set->str, buf, set->cur_pos - 12);
	set->cur_pos++;
}

void			all_ccmd(char *buf, t_set *set)
{
	if (buf[0] == 127 && ft_strlen(buf) == 1 && set->cur_pos > 12)
	{
		ft_dell(set);
		free_buff(buf);
	}
	else if (buf[0] == 9 && ft_strlen(buf) == 1)
		free_buff(buf);
	else if (ft_strlen(buf) >= 3 && buf[0] == 27)
		set_fle(set, buf);
	else if (ft_strlen(buf) == 1 && buf[0] == 4)
	{
		if (ft_strlen(set->str) == 0)
		{
			ft_putstr_fd("exit\n", STDERR);
			exit(0);
		}
		free_buff(buf);
	}
	else if ((set->str[set->cur_pos - 12] != ' ') && (buf[0] == 22 && buf[1] == 0 ) || (buf[0] == 6 && buf[1] == 0)
	|| (buf[0] == 18 && buf[1] == 0))
		is_copy_cut(set, buf);
	else if (buf[0] != 10 && buf[0] != 127)
		aff_modif_str(set, buf);
}

void			eeddn(t_set *set)
{
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str)] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
}
