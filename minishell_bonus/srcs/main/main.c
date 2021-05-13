/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:13:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 13:43:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			add_exval(t_set *set)
{
	char		*tmp;

	tmp = ft_itoa(set->exit_val);
	if (set->exit_v)
		free(set->exit_v);
	set->exit_v = ft_strjoin("?=", tmp);
	free(tmp);
	ft_hideenv(set->exit_v, set);
}

void			disp_prompt(void)
{
	ft_putstr_fd("\033[1;35mᴍ\033[1;33mɪ\033[1;31mɴ\033[1;36mɪ", STDERR);
	ft_putstr_fd("\033[1;32msʜᴇʟʟ\033[1;37m ➔\033[0m ", STDERR);
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;

	if (!(isatty(0)))
		return (0);
	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);
	while (1)
	{
		read_ent(set);
		treat_cmd(set);
	}
	return (0);
}
