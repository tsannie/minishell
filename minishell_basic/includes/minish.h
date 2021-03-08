/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/08 17:09:25 by phbarrad         ###   ########.fr       */
=======
/*   Updated: 2021/03/08 17:10:58 by tsannie          ###   ########.fr       */
>>>>>>> a6bfa2f6757901f00eb8870c20a37ffb49adc254
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
#include <fcntl.h>
#include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_set
{
	char	*str;
	char	*word_tmp;
	int		fd;

	int		exit;
	char	**arg;
	char	*cmd;
	int		y;
	int		l_dol;
	int		err_quote;
	int		err_redi;
	int 	exit_val;
	int		shlvl;
	int		run;
	int		pid;

	char 	*path;
	char	*pwd;
	char	*old_pwd;
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
void		ft_sort_dbtab(t_set *set);
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
char	*redirection(char *src, t_set *set);
char	*change_dol(char *dol, t_set *set);
char	*dolars_find(char *src, t_set *set);
int		antislash_pair(char *src, int i);
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
// init
char	*joinf(char *s1, char *s2, char *s3, char *s4);
int ft_menv(char *str, t_set *set);
char *ft_get_path(char **envp);
//
//bin
int		bash_cmd(t_set *set);

int			ft_strcmp(char *s1, char *s2);
/* TOOLS TO DELETE WHEN ITS END */
void	print_args(char **str);

#endif
