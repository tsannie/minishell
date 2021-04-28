/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 09:52:57 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 15:04:10 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	create_stdin(char *namefile, t_set *set)
{
	//char	*line;
	int		pipefd[2];
	char	buf[BUF_SIZE];

	(void)set;
	(void)namefile;
	ft_bzero((void *)buf, BUF_SIZE);
	pipe(pipefd);
	/*while (ft_streql)
	{
		ft_putstr_fd("> ", STDOUT);
		while ((ft_strcmp(buf, "\n") != 0)
		{
			read(0, buf, BUF_SIZE);
			ft_putstr_fd(buf, STDOUT);
			ft_bzero((void *)buf, BUF_SIZE);
		}
	}*/
	printf("bye\n");
}