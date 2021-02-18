/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/18 11:28:08 by phbarrad         ###   ########.fr       */
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
	char	*str;
	char	*word_tmp;

	char	**arg;
	char	*cmd;
	int		y;
	int		l_dol;
	int		err_quote;
	int 	exit_val;

	char 	*path;
	char	*pwd;
	int		cwplen;
	char	**hide_envp;
	char	**envp;
}				t_set;

//env
int ft_modenv(char *str, t_set *set);
int ft_hideenv(char *str, t_set *set);
void  ft_init_env(t_set *set, char **envp, char **av);
char *recup_new(char *str, int x);
char **ft_strdup_tabl(char **envp);
//
void	ft_putstr_not_found(char *str);
void 	ft_eexit(t_set *set);
int		ft_disp_export(t_set *set);
void	start_shell(int ac, char **av,   t_set *set);
void	treat_cmd(t_set *set);
void	start_cmd(  t_set *set);
char	**search_arg(char *str, t_set *set);
char	*search_dolars(char *src, t_set *set);
char	*add_letter(char *str, char a);
char	*before_equal(char *str);
int		search_quotes(const char *src, t_set *set, char a);
//cmd
int		ft_cd(t_set *set);
int 	ft_echo(t_set *set);
int 	ft_env(t_set *set);
int 	ft_export(t_set *set);
int 	ft_unset(t_set *set);
int 	ft_pwd(t_set *set);
//
int	ncmpel(char *s1, char *s2);
int checkenvp(char *str);
//
int		ncmpel(char *s1, char *s2);
char	**addword(char **res, int nb_word, t_set *set, char *word);
char	**split_semicolon(char *str, t_set *set);





/* TOOLS TO DELETE WHEN ITS END */
void	print_args(char **str);

#endif
