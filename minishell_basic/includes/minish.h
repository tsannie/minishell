/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/15 14:07:03 by tsannie          ###   ########.fr       */
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

	char	**arg;
	char	*cmd;
	int		y;
	int		err_quote;

	int		cwplen;
	char	**hide_envp;
}				t_set;

void 	ft_eexit(t_set *set);
int		ft_disp_export(t_set *set);
void	start_shell(int ac, char **av, char **envp, t_set *set);
int		ft_cd(t_set *set);
int		ft_echo(t_set *set);
int		ft_env(t_set *set, char **envp);
int		ft_export(t_set *set, char **envp);
int		ft_unset(t_set *set, char **envp);
int		ft_pwd(t_set *set);
void	treat_cmd(t_set *set, char **envp);
void	start_cmd(char **envp, t_set *set);
char	**search_arg(char *str, t_set *set);
char	*add_letter(char *str, char a);

int		ft_cd(t_set *set);
int 	ft_echo(t_set *set);
int 	ft_env(t_set *set, char **envp);
int 	ft_export(t_set *set, char **envp);
int 	ft_unset(t_set *set, char **envp);
int 	ft_pwd(t_set *set);

int 	ft_strcmpp(char *s1, char *s2);

#endif
