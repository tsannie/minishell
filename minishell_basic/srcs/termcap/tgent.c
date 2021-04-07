/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgent.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:18:39 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

void			add_history(t_set *set)
{
	if (set->str != NULL)
	{
		if (ft_strlen(set->str) > 0)
		{
			if (set->inc_his == 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
			}
			else if (ft_strcmp(set->history[set->inc_his - 1], set->str) != 0)
			{
				set->inc_his++;
				set->history = addword(set->history, set->inc_his, set->str);
			}
		}
	}
	set->his_pos = set->inc_his; 
/* 	int x = -1;
	while (set->history[++x])
		printf("::[%s]\n", set->history[x]); */	
}

/* else if (buf[2] == 72)
			move_line_start(set);
		else if (buf[2] == 70)
			move_line_end(set); */

int			set_fle(t_set *set, char *buf)
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
	int i;
	char *new;

	i = 0;
	if (!str)
		return (NULL);
	if (!(new = malloc(sizeof(char) * (len))))
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

void			read_ent(t_set *set)
{
	int		parse;
	char	buf[BUF_SIZE];
	size_t	buf_len;
	int i = 0;

	ffree(set->str);
	set->str = ft_strdup("");
 	while (i == 0)
	{
		ft_bzero((void *)buf, BUF_SIZE);
		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		//printf("[%s][%d][%d]\n", buf, ft_strlen(buf), buf[0]);
		if(buf[0] == 127)
		{
			//printf("oui\n");
			set->str = ft_strdup_free_len(set->str, ft_strlen(set->str) - 1);
		}
		else
			set->str = ft_strjoin_free(set->str, buf);
		ft_putstr_fd(buf, STDERR);
		if (ft_strlen(buf) == 3 && buf[0] == 27)
			set_fle(set, buf);
		if (ft_strcmp(buf, "\n") == 0)
			i = 1;
	}
	i = 0;
	set->str[ft_strlen(set->str) - 1] = '\0';
	add_history(set);
}

int			init_tgent(t_set *set)
{
	(void)set;
/* 	int			term;
	char		*term_type;
	int ret;

	ttyname(0)
	set->line_count = tgetnum("li");
	printf("line_count = [%d]\n", set->line_count);
	term_type = getenv("TERM");
    if (term_type == NULL)
        return (-1);
	ret = tgetent(NULL, term_type);
	if (ret != 1)
        return (-1);
	printf("[%d][%s]\n", ret, term_type);




	char *ku;
	char *kd;

	char *cl_string;
	char *cm_string;
	int auto_wrap;
	int height;
	int width;
	char *temp;
	char *BC;
	char *UP;
	char *DO;

			ku = tgetstr("ku", NULL);
			kd = tgetstr("kd", NULL);

			printf("\n\n\n\nku  [%s]==[%s]\n\n\n\n\n",set->cmd, ku);
			printf("\n\n\n\nkd  [%s]==[%s]\n\n\n\n\n",set->cmd, kd);

			//cl_string = tgetstr("cl", NULL);
			cm_string = tgetstr("cm", NULL);
			auto_wrap = tgetflag("am");
			height = tgetnum("li");
			width = tgetnum("co");
			temp = tgetstr("pc", NULL);
			BC = tgetstr("le", NULL);
			UP = tgetstr("up", NULL);
			DO = tgetstr("do", NULL); */
	return (0);
}