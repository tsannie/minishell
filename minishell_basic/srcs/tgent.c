/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgent.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:15:37 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 10:50:36 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int			init_tgent(t_set *set)
{
	int			term;
	char		*term_type;
	int ret;

	set->line_count = tgetnum("li");
	printf("line_count = [%d]\n", set->line_count);
	term_type = getenv("TERM");
    if (term_type == NULL)
        return (-1);
	ret = tgetent(NULL, term_type);
	if (ret != 1)
        return (-1);
	printf("[%d][%s]\n", ret, term_type);
	return (0);
}