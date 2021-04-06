/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgent.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
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
	int x = -1;
	while (set->history[++x])
		printf("::[%s]\n", set->history[x]);	
}

void			read_ent(t_set *set)
{
	int		parse;
	char	buf[BUF_SIZE];
	size_t	buf_len;
	int i = 0;
	char *tmp;

	ffree(set->str);
	set->str = ft_strdup("");
	set->str = get_val(set);
 	while (1)
	{
		ft_bzero((void *)buf, BUF_SIZE);
		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		//printf("\n[%s][%d]\n", buf, ft_strlen(buf));
		tmp = ft_strjoin(set->str, buf);
		ffree(set->str);
		set->str = ft_strdup(tmp);
		ffree(tmp);
		ft_putchar_fd(buf, STDERR);
		i++;
	}
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