/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgent.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/25 15:49:09 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

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
	//printf("len = [%d]\n", len);
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

void		ft_puttermcaps(char *str)
{
	char	*res;
	char	*env;

	env = getenv("TERM");
	if ((res = tgetstr(str, &env)) == NULL)
		return ;
	tputs(res, 0, putchar);
}


/* void		ft_get_beggin_with_curs(t_set *set)
{
	while ((pos) && set->str[(pos)] != '\n')
	{
		--(pos);
		ft_puttermcaps("le");
	}
	if (!pos &&  set->str[(pos)] != '\n')
		ft_puttermcaps("le");
	if (set->str[(pos)] == '\n')
		++(pos);
}
 */
/* 
size_t	get_cursor_x_pos(t_input *input, t_input *pos, size_t p_len)
{
	size_t	i;
	t_input	*tmp;

	i = 1;
	if (!(tmp = input) || !(pos))
		return (p_len + 1);
	while (tmp && tmp != pos)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + p_len);
}

void	replace_cursor(t_set *set, int print, int back)
{
	size_t	x_pos;
	size_t	col;
	int		overflow;

	col = set->col;
	x_pos = get_cursor_x_pos(set->input, set->curs_pos, 13);
	overflow = lst_len(set->curs_pos) - set->winsize + set->col;
	if ((!print && back && ((x_pos % col) == 0)) || (print == 42))
	{
		tputs(tgetstr("up", NULL), set->fd[3], &putchar);
		while (col--)
			tputs(tgetstr("nd", NULL), set->fd[3], &putchar);
	}
	else if (back)
		tputs(tgetstr("le", NULL), set->fd[3], &putchar);
	else if ((overflow < 0) && ((x_pos % set->col) == 0))
		tputs(tgetstr("do", NULL), set->fd[3], &putchar);
	else if (overflow >= 0 && ((x_pos % set->col) == 0))
	{
		while (col--)
			tputs(tgetstr("le", NULL), set->fd[3], &putchar);
	}
	else
		tputs(tgetstr("nd", NULL), set->fd[3], &putchar);
}
 */


int			ft_dell(t_set *set)
{
	size_t col;
	size_t len;

	len = ft_strlen(set->str);
	col = set->col;
	set->str = ft_strdup_free_len(set->str, len);
	if (len > 0)
	{
		//printf("\n[%d]\n", len);
		ft_putstr_fd(set->tt_left, STDERR);
		ft_putstr_fd(" ", STDERR);
		ft_putstr_fd(set->tt_left, STDERR);
	}
	//printf("[%s][%d]\n", set->str, ft_strlen(set->str));
	//while (len--)
/* 	ft_putstr_fd("\033[1K",STDERR);
	ft_putstr_fd("\r",STDERR);
 	if (len > col - 12)
	{
		ft_putstr_fd("\033[1K",STDERR);
		ft_putstr_fd(set->tt_up, STDERR);
		ft_putstr_fd("\033[1K",STDERR);
		ft_putstr_fd("\r",STDERR);
		//ft_putstr_fd("\n", STDERR);
		len = len - col;
	}
 	disp_prompt();
	ft_putstr_fd(set->str, STDERR); */
	return (0);
}		

void			read_ent(t_set *set)
{
	int		parse;
	char	buf[BUF_SIZE];
	size_t	buf_len;
	int i = 0;

	ffree(set->str);
	set->str = ft_strdup("");
	//ft_puttermcaps("cl");

 	while (i == 0)
	{
		start_term(set);
		ft_bzero((void *)buf, BUF_SIZE);
		//ft_putstr_fd("\r", STDERR);

		if (read(0, buf, BUF_SIZE) == -1)
			ft_putstr_fd("err\n", STDERR);
		//printf("[%s][%d][%d][%d][%s]\n", buf, ft_strlen(buf), buf[0], ft_strlen(set->str), set->str);
		if(buf[0] == 127 && ft_strlen(buf) == 1)
			buf[0] = ft_dell(set);
		else if (buf[0] == 9 && ft_strlen(buf) == 1)
			buf[0] = 0;
		else if (ft_strlen(buf) == 3 && buf[0] == 27)
		{
			set_fle(set, buf);
			buf[0] = 0;
			buf[1] = 0;
		}
		else
			set->str = ft_strjoin_free(set->str, buf);
		ft_putstr_fd(buf, STDERR);
		if (ft_strcmp(buf, "\n") == 0)
			i = 1;
	}
	i = 0;
	//printf("[%s]\n", set->str);
	if (ft_strlen(set->str) > 0)
		set->str[ft_strlen(set->str) - 1] = '\0';
	else
		set->str[1] = '\0';
	add_history(set);
}

int			init_tgent(t_set *set)
{
	(void)set;

	return (0);
}

/*
void			ft_dell(t_set *set)
{
	size_t col;
	size_t len;
	len = ft_strlen(set->str);

	col = set->col;
	//printf("[%d]\n", set->col);
 
	//printf("%d\n", len);
	//tputs(tgetstr("cd", NULL), set->fd[3], &putchar);
 	//while (len > 1)
	//{
		//ft_putstr_fd("iui\n",STDERR);

		//ft_putstr_fd("\b", STDERR);
	//	len--;
	//}
//	

	//ft_putstr_fd("\033[s\033[7B\033[1;34m 7 lines down violet \033[u\033[0m",STDERR);

	//ft_putstr_fd("\033[3K",STDERR);

 	disp_prompt();
 	while (len > 1)
	{
		ft_putstr_fd(" ", STDERR);
		len--;
	}
	ft_putstr_fd("\r",STDERR);
	disp_prompt();
	ft_putstr_fd(set->tt_left, STDERR);
	ft_putstr_fd(" ok", STDERR);
	//ft_putstr_fd(set->tt_left, STDERR);

	//set->str = ft_strdup_free_len(set->str, ft_strlen(set->str) - 1);
	//ft_putstr_fd(set->str, STDERR);
			
}
*/