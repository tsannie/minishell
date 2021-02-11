/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/11 10:11:53 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISH_H
# define MINISH_H

# include "../../libft/libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct	s_set
{
	char 	*str;
	int		cwplen;
}				t_set;



void	start_shell(int ac, char **av, char **envp, t_set *set);
int ft_cd(t_set *set);
int ft_echo(t_set *set);
int ft_env(t_set *set, char **envp);
int ft_export(t_set *set, char **envp);
int ft_unset(t_set *set, char **envp);
int ft_pwd(t_set *set);

int ft_strcmpp(char *s1, char *s2);

#endif
