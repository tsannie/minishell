/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/12 14:33:08 by phbarrad         ###   ########.fr       */
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

# define LLU_MAX 18446744073709551615
# define LLU_MIN -9223372036854775809

typedef struct	s_set
{
	char	*str;
	char	*word_tmp;
	int		fdout;
	int		fdin;
	int		pipeout;
	int		pipein;
	int		save_stdout;
	int		save_stdin;
	int		stop;

	int		exit;
	char	**arg;

	char	**all_path;

	char	*cmd;
	char	*lastcmd;

	int		y;
	int		p;
	int		l_dol;
	int		err_quote;
	int		err_redi;
	int 	exit_val;
	char 	*exit_v;

	char	*shlvl;
	int		run;
	int		pid;

	char 	*pathbc;
	char 	*path;
	char	*pwd;
	char	*old_pwd;
	int		cwplen;
	char	**hide_envp;
	char	**envp;
}				t_set;

//lib
char	**ft_splitbc(const char *str, char charset);
void			add_exval(t_set *set);
//env
unsigned long long		ft_atoill(const char *str);
int ft_modenv(char *str, t_set *set);
int ft_hideenv(char *str, t_set *set);
void  ft_init_env(t_set *set, char **envp, char **av);
char *recup_new(char *str, int x);
char **ft_strdup_tabl(char **envp);
void		ft_sort_dbtab(t_set *set);
//
int		is_pipe(char *str);
int		forwar_quote(char *src, int i);
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
char	*before_equale(char *str);
int		search_quotes(const char *src, t_set *set, char a);
char	*redirection(char *src, t_set *set);
char	*change_dol(char *dol, t_set *set);
char	*dolars_find(char *src, t_set *set);
int		antislash_pair(char *src, int i);
char	*start_pipe(char *str, t_set *set);
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
char	*maj_to_min(char *str);

//bin
void	get_lastcmd(t_set *set);
int					bash_cmd(t_set *set, char *cmd);
int		check_shlvl(t_set *set, char **envp);
int			ft_strcmp(char *s1, char *s2);
/* TOOLS TO DELETE WHEN ITS END */
void	print_args(char **str);

#endif
