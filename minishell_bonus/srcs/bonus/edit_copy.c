/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   edit_copy.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: user42 <user42@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/04/06 15:32:30 by phbarrad		  #+#	#+#			 */
/*   Updated: 2021/04/29 15:25:41 by user42		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int			 ft_strlen_space(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char			*ft_strdup_space_len(char *str, int pos)
{
	char *new;
	int len;
	int i;
	int e;

	e = 0;
	i = 0;
	len = 0;
	while (str[i] && i < pos)
		i++;
	while (str[i] != ' ' && i >= 0)
		i--;
	i++;
	len = ft_strlen_space(str + i);
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (str[i + e] != ' ' && str[i + e])
	{
		new[e] = str[i + e];
		e++;
	}
	new[e] = 0;
	return (new);
}



void			go_copy(t_set *set, char *buf)
{

	ffree(set->edit_copy);
	set->edit_copy = ft_strdup_space_len(set->str, set->cur_pos - 12);
	printf("[%s]\n", set->edit_copy);
}

void			go_cut(t_set *set, char *buf)
{
	while (set->str[set->cur_pos - 12] != ' ' && set->str[set->cur_pos - 12])
	{
		ft_putstr_fd(set->tt_right, STDERR);
		set->cur_pos++;
	}
	//set->cur_pos++;
	//ft_putstr_fd(set->tt_right, STDERR);
	//ft_dell(set);
	//while (set->str[set->cur_pos - 12])// != ' ' && set->cur_pos - 12 > 0)
	//	ft_dell(set);

}
void			go_paste(t_set *set, char *buf)
{

}
void			is_copy_cut(t_set *set, char *buf)
{
	if (buf[0] == 22 && buf[1] == 0)
		go_copy(set, buf);
	else if (buf[0] == 6 && buf[1] == 0)
		go_cut(set, buf);
	else if (buf[0] == 18 && buf[1] == 0)
		go_paste(set, buf);
	else
		return ;
	free_buff(buf);
}