/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:29:50 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/09 13:34:33by user42           ###   ########.fr       */
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

void			revenir_pos(t_set *set)
{
	size_t		len;
	size_t		col;
	int cursor;

	int e = 0;
	int x = 0;
	cursor = set->cur_pos - 1;
	col = set->col;
	len = ft_strlen(set->str) + 12;

/*   	if ((x == 0) && (ft_strlen(set->str) + 13 != set->cur_pos)
	&& (ft_strlen(set->str) + 12 != set->col))
	{
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
	}
 */	while (len > cursor)
	{
 		if (((len) % col) == 0 && x != 0 && len >= col)
		{
			//if (ft_strlen(set->str) + 12 == set->col)
				//ft_putstr_fd("\033[2K", STDERR);
			ft_putstr_fd(set->tt_up, STDERR);
			//ft_putstr_fd("\n\n\noui\n\n\n", STDERR);
			while (e++ < col)
				ft_putstr_fd(set->tt_right, STDERR);
		}
		else
			ft_putstr_fd(set->tt_left, STDERR);
		len--;
		e = 0;
		x++;
	}
  /*	if ((ft_strlen(set->str) + 12 == col) &&
	(ft_strlen(set->str) + 13 != set->cur_pos))
	{
//		printf("\n\n\n[%d][%d]\n\n\n",ft_strlen(set->str) + 13, set->cur_pos);
		ft_putstr_fd(set->tt_right, STDERR);
		//ft_putstr_fd(set->tt_right, STDERR);
	} */
}

int				ft_dell(t_set *set)
{
	size_t		len;
	size_t		col;
	int e = 0;

	col = set->col;	
	len = ft_strlen(set->str);
	set->str = ft_strdup_free_pos(set->str, len, set->cur_pos - 13);
	set->dell_len = getdellen(set->cur_pos, col);
	if (set->cur_pos - 12 > 0)
	{
		if ((set->cur_pos % col) == 0)
		{
			ft_putstr_fd(set->tt_up, STDERR);
			while (++e < len + 12)
				ft_putstr_fd(set->tt_right, STDERR);
			ft_putstr_fd("  ", STDERR);
			e = 0;
			ft_putstr_fd(set->tt_up, STDERR);
			while (++e < len + 12)
				ft_putstr_fd(set->tt_right, STDERR);
			ft_putstr_fd(set->tt_right, STDERR);
		}
		else
		{
			ft_putstr_fd(set->tt_left, STDERR);
			ft_putstr_fd(" ", STDERR);
			ft_putstr_fd(set->tt_left, STDERR);
		}
		ft_putstr_fd(set->str + (set->cur_pos - 13), STDERR);
 	  	/* if ((ft_strlen(set->str) + 13 != set->cur_pos)
		&& (ft_strlen(set->str) + 12 != set->col))
		{
			ft_putstr_fd(" ", STDERR);
			ft_putstr_fd(set->tt_left, STDERR);
		}
 */		revenir_pos(set);
	}
	set->cur_pos--;
	//aff_dell(set);
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

int			aff_modif_str(t_set *set, char *buf)
{
	size_t		len;
	size_t		col;
	int e;

	e = 0;
	col = set->col;
	set->str = ft_strjoin_free_len(set->str, buf, set->cur_pos - 12);
	len = ft_strlen(set->str) + 12;
	set->cur_pos++;
	if (set->cur_pos - 12 < ft_strlen(set->str))
	{
		ft_putstr_fd(buf, STDERR);
		ft_putstr_fd(set->str + (set->cur_pos - 12), STDERR);
		if ((len % col) == 0)
		{
			ft_putstr_fd(" ", STDERR);
			ft_putstr_fd(set->tt_left, STDERR);
		}
 		while (len > set->cur_pos)
		{
		 	 if (((len) % col) == 0)
			{
				ft_putstr_fd(set->tt_up, STDERR);
				while (++e < col)
					ft_putstr_fd(set->tt_right, STDERR);
			}
			else  
				ft_putstr_fd(set->tt_left, STDERR);
			len--;
			e = 0;
		}
		return (1);
	}
	return (0);
}

void			all_ccmd(char *buf, t_set *set)
{
	int oui = 0;
	if (buf[0] == 127 && ft_strlen(buf) == 1)
	{
		if (set->cur_pos > 12)
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
	else if (((set->str[set->cur_pos - 12] != ' ')) &&
	((buf[0] == 22 && buf[1] == 0 ) || (buf[0] == 6 && buf[1] == 0) ||
	(buf[0] == 18 && buf[1] == 0))) 
		is_copy_cut(set, buf);
	else if (buf[0] != 10 && buf[0] != 127)
		oui = aff_modif_str(set, buf);
	if (oui == 0)
		ft_putstr_fd(buf, STDERR);
}

void			eeddn(t_set *set)
{
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str)] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
}
