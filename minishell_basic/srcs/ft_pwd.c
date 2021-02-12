/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:32 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 13:31:38 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_pwd(t_set *set)
{
    char *cwd;
    char buff[4096 + 1];

    cwd = getcwd(buff, 4097);
    printf("%s\n",cwd);
    return (0);
}
