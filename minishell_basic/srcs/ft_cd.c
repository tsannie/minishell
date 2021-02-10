/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:39 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 15:22:22 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char *ft_getenv(void)
{
    char *cwd;
	char *result;
	char buff[4096 + 1];
    int i = 0;
	int e = -2;
	int r = -3;

    cwd = getcwd(buff, 4097);
	result = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
    while (cwd[i])
    {
        if (cwd[i] == '/')
            e++;
        i++;
    }
    while (e > 0)
    {
        r += 3;
        result[r] = '.';
        result[r+1] = '.';
        result[r+2] = '/';
        e--;
    }
    result[r+3] = '\0';
    return (result);
}

int		real_path(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	i += 2; // + cd
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int		ft_cd(t_set *set)
{
	int i;
	int valid;

	i = real_path(set->str);
	valid = chdir(set->str + i);
	if (ft_strlen(set->str + i) == 0)
		return (chdir(ft_getenv()));
	if (valid == -1)
		printf("minish: cd: %s: No such file or directory\n", set->str + i);
	//printf("chdir = [%d]\n", valid);
    return (0);
}