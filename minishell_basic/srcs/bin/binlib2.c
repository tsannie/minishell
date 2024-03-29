/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binlib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:28:38 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 12:37:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int					ft_strcmpss(char *s1, char *s2)
{
	int				i;

	i = 0;
	if (ft_strlen(s1) - 1 != ft_strlen(s2))
		return (1);
	while (s1[i] == s2[i] && s1[i] && s1[i + 1] != '/')
		i++;
	return (s1[i] - s2[i]);
}

int					ft_strcmpsl(char *s1, char *s2)
{
	int				i;
	int				len;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	if (s1[len - 1] == '/')
		len--;
	while (s1[i] == s2[i] && s1[i] && i < len)
		i++;
	return (s1[i] - s2[i]);
}

int					finn(t_set *set, char *path, char *cmd)
{
	int ret;

	ret = chemin_path(set->chemin, path, set, cmd);
	ffree(path);
	free(cmd);
	return (ret);
}

void				start_term2(t_set *set)
{
	tcgetattr(0, &set->term);
	set->term.c_lflag |= (ICANON | ECHO | ISIG);
	tcsetattr(0, 0, &set->term);
}
