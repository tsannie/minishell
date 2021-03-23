/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 13:31:58 by phbarrad         ###   ########.fr       */
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
#include <sys/stat.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include <fcntl.h>
#include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_sig
{
	int				run;
	int				pid;
}				t_sig;

typedef struct	s_set
{
	char	*str;
	char	*word_tmp;
	char	**push;
	int		fdout;
	int		fdin;
	int		pipeout;
	int		pipein;
	int		ex_pi;
	int		start_end;
	int		save_stdout;
	int		save_stdin;
	int		stop;
	int		parents;
	int		last;
	int		no_exec;
	int		simple;
	int		ret_value;
	char	*dol_amb;
	int		amb;
	int		not_exist;

	int		bleu;
	int		pid;
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

	char 	*pathbc;
	char 	*path;
	char	*pwd;
	char	*old_pwd;
	int		cwplen;
	char	**hide_envp;
	char	**envp;
}				t_set;

//lib
char			**ft_splitbc(const char *str, char charset);
void			add_exval(t_set *set);
char			*ft_strduplen(const char *s1, int len);
int				is_dir(char *arg);
//env
unsigned long long		ft_atoill(const char *str);
int ft_modenv(char *str, t_set *set);
int ft_hideenv(char *str, t_set *set);
void  ft_init_env(t_set *set, char **envp, char **av);
char *recup_new(char *str, int x);
char **ft_strdup_tabl(char **envp);
void		ft_sort_dbtab(t_set *set);
int				ft_unsethideenv(t_set *set, char *str);
int				ft_unsetenv(t_set *set, char *str);

//
void	ifclose(int fd);
int		is_pipe(char *str);
int		forwar_quote(char *src, int i);
void	ft_putstr_not_found(char *str, t_set *set);
void 	ft_eexit(t_set *set);
int		ft_disp_export(t_set *set);
void	start_shell(int ac, char **av, t_set *set);
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
int		start_pipe(t_set *set);
char	**split_pipe(char *str, t_set *set);
void	exec_cmd(t_set *set, char *cmd);
void	reset_fd(t_set *set);
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
char			*maj_to_min(char *str);
int				is_dir_present(char *arg, char *cmd);
//export
int 			ft_egenv(char *str, t_set *set);
int				ft_eghide(char *arg, t_set *set);
char			*st_moin_pe(char *str);
char			*double_slash(char *arg);
int				ncmpelp(char *s1, char *s2);
//
//bin
void	get_lastcmd(t_set *set);
int					bash_cmd(t_set *set, char *cmd);
int		check_shlvl(t_set *set, char **envp);
int			ft_strcmp(char *s1, char *s2);
/* TOOLS TO DELETE WHEN ITS END */
void	print_args(char **str);


char *get_val(t_set *set);
#endif
