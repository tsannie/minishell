/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:13:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/26 14:35:39 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

void			disp_prompt(void)
{
	ft_putstr_fd("\033[1;35mᴍ\033[1;33mɪ\033[1;31mɴ\033[1;36mɪ", STDERR);
	ft_putstr_fd("\033[1;32msʜᴇʟʟ\033[1;37m ➔\033[0m ", STDERR);
}

int				main(int ac, char **av, char **envp)
{
	t_set		*set;
	int			ret;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (init_all(set, envp) == -1)
		return (-1);
	ret = 0;
	if (ac == 3)
		ret = start_shell(ac, av, set);
	else
	{
		while (1)
		{
			read_ent(set);
			treat_cmd(set);
		}
	}
	return (ret);
}
