/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 17:02:45 by phbarrad         ###   ########.fr       */
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
	int		nb_word;
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

	int		line_count;

	int		ex_er;
	int		len;
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

int						get_next_line(int fd, char **line);
//lib
char					**ft_splitbc(const char *str, char charset);
void					add_exval(t_set *set);
char					*ft_strdupbc(const char *s1);
int						is_dir(char *arg);
//env
unsigned long long		ft_atoill(const char *str);
int						ft_modenv(char *str, t_set *set);
int						ft_hideenv(char *str, t_set *set);
void					ft_init_env(t_set *set, char **envp, char **av);
char					*recup_new(char *str, int x);
char					**ft_strdup_tabl(char **envp);
void					ft_sort_dbtab(t_set *set);
int						ft_unsethideenv(t_set *set, char *str);
int						ft_unsetenv(t_set *set, char *str);

//
int						first_semicon(const char *str);
int						multi_redirecion(char *src, t_set *set, char a);
int						correct_cmd(char *str, t_set *set);
int						call_err(int e, t_set *set);
int						check_pipe(const char *str, int i);
int						first_part(const char *str, t_set *set);
int						err_code(char *src, int i, t_set *set);
int						error_list(int a, t_set *set);
void					ifclose(int fd);
int						is_pipe(char *str);
int						forwar_quote(char *src, int i);
void					ft_putstr_not_found(char *str, t_set *set);
void 					ft_eexit(t_set *set);
int						ft_disp_export(t_set *set);
void					start_shell(int ac, char **av, t_set *set);
void					treat_cmd(t_set *set);
void					start_cmd(  t_set *set);
void					search_arg(char *str, t_set *set);
char					*search_dolars(char *src, t_set *set);
char					*add_letter(char *str, char a);
char					*before_equal(char *str);
char					*before_equale(char *str);
int						search_quotes(const char *src, t_set *set, char a);
void					search_basic(const char *str, t_set *set);
char					*redirection(char *src, t_set *set);
char					*change_dol(char *dol, t_set *set);
char					*dolars_find(char *src, t_set *set);
int						antislash_pair(char *src, int i);
void					start_pipe(t_set *set);
char					**split_pipe(char *str, t_set *set);
void					exec_cmd(t_set *set, char *cmd);
void					reset_fd(t_set *set);
//cmd
int						ft_cd(t_set *set);
int						ft_echo(t_set *set);
int						ft_env(t_set *set);
int						ft_export(t_set *set);
int						ft_unset(t_set *set);
int						ft_pwd(t_set *set);
//
int						ncmpel(char *s1, char *s2);
int						checkenvp(char *str);
//
int						ncmpel(char *s1, char *s2);
char					**addword(char **res, int nb_word, t_set *set, char *word);
char					**split_semicolon(char *str, t_set *set);
// init
char					*joinf(char *s1, char *s2, char *s3, char *s4);
int						ft_menv(char *str, t_set *set);
char					*ft_get_path(char **envp);
//
char					*maj_to_min(char *str);
int						is_dir_present(char *arg, char *cmd);
//export
int 					ft_egenv(char *str, t_set *set);
int						ft_eghide(char *arg, t_set *set);
char					*st_moin_pe(char *str);
char					*double_slash(char *arg);
int						ncmpelp(char *s1, char *s2);
//
//bin
int				ft_strcmpss(char *s1, char *s2);
int				is_dir_presentsl(char *arg, char *cmd);
int				exec_bin(t_set *set, char *path, char *cmd);
void			get_lastcmd(t_set *set);
char			*get_path(t_set *set, char *path, char *cmd);
char			*get_path_chemin(t_set *set, char *path, int len, char *cmd);
char			*cmd_in_pwd(t_set *set, char *cmd);
int				ft_strlenbc(char *str);
int				check_sh(t_set *set, char *path);
int				check_stat_file(t_set *set, char *path, char *cmd);
char			**new_args(char **args, t_set *set, char *cmd);
int				ft_strcmpsl(char *s1, char *s2);
int				bash_cmd(t_set *set, char *cmd);
int				check_shlvl(t_set *set, char **envp);
int				ft_strcmp(char *s1, char *s2);
//init
int				init_tgent(t_set *set);
int				init_all(t_set *set, char **envp, char **av);
int				free_all(t_set *set, int ret);
/* TOOLS TO DELETE WHEN ITS END */
void			print_args(char **str);
char			*get_val(t_set *set);
#endif
