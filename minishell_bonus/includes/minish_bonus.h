/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:07:34 by phbarrad          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/13 12:40:24 by user42           ###   ########.fr       */
=======
/*   Updated: 2021/05/13 12:44:47 by tsannie          ###   ########.fr       */
>>>>>>> 1a151b9d683304d1bc125134af49ce9e55b035bf
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_BONUS_H
# define MINISH_BONUS_H

# include "../../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>

# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUF_SIZE 4096

typedef struct			s_sig
{
	int					run;
	int					pid;
}						t_sig;

typedef struct			s_set
{
	struct termios		term;
	struct termios		term_backup;

	int 				fl;
	char				*credir;
	char 				*edit_copy;
	int					cur_pos;
	int					dell_len;
	int					dell_his;
	char				*str;
	char				*word_tmp;
	char				**push;
	char				**list;
	char				*redirect;
	int					nb_word;
	int					fdout;
	int					fdin;
	int					start_end;
	int					save_stdout;
	int					save_stdin;
	int					stop;
	int					last;
	int					no_exec;
	int					simple;
	char				*dol_amb;
	int					dol_found;
	int					amb;
	int					not_exist;
	int					wait;
	int					line_count;
	int					g;
	int					ex_er;
	int					len;
	int					bleu;
	int					pid;
	int					exit;
	char				**arg;
	char				*namefile;
	char				**all_path;
	char				*cmd;
	char				*lastcmd;
	int					lene;
	int					chemin;
	int					y;
	int					p;
	int					l_dol;
	int					err_quote;
	int					err_redi;
	int					exit_val;
	char				*exit_v;
	char				*shlvl;
	int					run;
	char				**history;
	int					inc_his;
	int					his_pos;
	int					col;
	int					row;
	int					winsize;
	char				*tt_up;
	char				*tt_down;
	char				*tt_left;
	char				*tt_right;
	char				*tt_home;
	char				*tt_end;
	char				*tt_ctl_up;
	char				*tt_crl_down;
	char				*pathbc;
	char				*path;
	char				*pwd;
	char				*old_pwd;
	int					cwplen;
	char				**hide_envp;
	char				**envp;
	char				**argss;
	int					r;
	int					w;
	int					x;
	int					d;
	char				**file;
	char				**fnd_file;
	int					com_w;
	char				**valid_file;
	char				*all_wild;
	int					empty_wild;
}						t_set;

void					start_term2(t_set *set);
char					*ft_strjoin_free_len(char *s1, char *s2, int len);

void					go_g(t_set *set);
void					go_d(t_set *set, int col);
void					is_prompt(t_set *set);
void					fg_o_fd(t_set *set, int x, int r, int col);
void					revenir_pos(t_set *set, size_t len);
int						ft_dell(t_set *set);
char					*ft_strdup_free_len(char *str, int len);
char					*ft_strdup_free_pos(char *str, int len, int pos);
void					aff_end_col(t_set *set, size_t len);

int						set_fle(t_set *set, char *buf);
void					is_copy_cut(t_set *set, char *buf);
int						ft_dell(t_set *set);

void					init_his(t_set *set);
void					add_history(t_set *set);
void 					free_buff(char *buf);
int						aff_modif_str(t_set *set, char *buf);
void					aff_buf(t_set *set, char *buf);
void					aff_dellnl(t_set *set);

void					start_term(t_set *set);
void					all_ccmd(char *buf, t_set *set);
void					eeddn(t_set *set);
int						getdellen(size_t len, size_t col);
void					aff_dell(t_set *set);

int						move_left(t_set *set);
int						move_right(t_set *set);
int						history_prev(t_set *set);
int						history_next(t_set *set);
char					*ft_strdup_free_len(char *str, int len);
char					*ft_strjoin_free_len(char *s1, char *s2, int len);

void					read_in(t_set *set);
void					read_ent(t_set *set);

char					**ft_splitbc(const char *str, char charset);
void					add_exval(t_set *set);
char					*ft_strdupbc(const char *s1);
int						is_dir(char *arg);
void					ffree(char *str);
char					*maj_to_min(char *str);
int						check_last(t_set *set);
int						eglinstr(char *str);

void					ft_putstr_not_found(char *str, t_set *set);
int						ft_putstr_error_quote(t_set *set);

unsigned long long		ft_atoill(const char *str);
int						ft_modenv(char *str, t_set *set);
int						ft_hideenv(char *str, t_set *set);
void					ft_init_env(t_set *set);
char					**ft_strdup_tabl(char **envp);
void					ft_sort_dbtab(t_set *set);
char					**ft_unsethideenv(t_set *set, char *str);
char					**ft_unsetenv(t_set *set, char *str);

int						err_folder(t_set *set, char *namefile, int i);

int						first_pipe(const char *str);
char					*get_newcmd(char *src, t_set *set, int i);
void					check_err_and_incr(t_set *set, int *i);
void					err_exist(t_set *set, char *namefile);
void					refresh_amb(char *dol, t_set *set);
char					*dolars_redirect(char *src, t_set *set);
char					*get_namefile(char *src, t_set *set, int i);
int						first_semicon(const char *str);
int						multi_redirecion(char *src, char a);
int						correct_cmd(char *str, t_set *set);
int						call_err(int e, t_set *set);
int						check_pipe(const char *str, int i);
int						first_part(const char *str, t_set *set);
int						err_code(char *src, int i);
int						error_list(int a, t_set *set);
void					ifclose(int fd);
int						is_pipe(char *str);
int						forwar_quote(char *src, int i);
void					ft_putstr_not_found(char *str, t_set *set);
void					ft_eexit(t_set *set);
int						ft_disp_export(t_set *set);
int						start_shell(int ac, char **av, t_set *set);
void					treat_cmd(t_set *set);
void					start_cmd(t_set *set);
void					search_arg(char *str, t_set *set);
void					search_cmd(const char *src, t_set *set);
char					*search_dolars(char *src, t_set *set);
char					*add_letter(char *str, char a);
char					*before_equal(char *str);
char					*before_equale(char *str);
int						search_quotes(const char *src, t_set *set, char a);
void					search_basic(const char *str, t_set *set);
char					*redirection(char *src, t_set *set);
char					*change_dol(char *dol, t_set *set);
char					*dolars_find(char *src);
int						antislash_pair(char *src, int i);
void					start_pipe(t_set *set);
char					**split_pipe(char *str, t_set *set);
void					exec_cmd(t_set *set, char *cmd);
void					reset_fd(t_set *set);

int						ft_check_valid_exit(t_set *set);
int						ft_cd(t_set *set);
int						ft_echo(t_set *set);
int						ft_env(t_set *set);
int						ft_export(t_set *set);
int						ft_unset(t_set *set);
int						ft_pwd(t_set *set);

int						ncmpel(char *s1, char *s2);
int						checkenvp(char *str);

int						ncmpel(char *s1, char *s2);
char					**addword(char **res, int nb_word, char *word);
char					**split_semicolon(char *str, t_set *set);

char					*joinf(char *s1, char *s2, char *s3, char *s4);
int						ft_menv(char *str, t_set *set);
char					*ft_get_path(char **envp);
void					rres(char **res, int word, int n, char str);

char					*maj_to_min(char *str);
int						is_dir_present(char *arg, char *cmd);

int						ft_egenv(char *str, t_set *set);
int						ft_eghide(char *arg, t_set *set);
char					*st_moin_pe(char *str);
char					*double_slash(char *arg);
int						ncmpelp(char *s1, char *s2);

int						chemin_path(int chemin, char *path, t_set *set,
char *cmd);
int						finn(t_set *set, char *path, char *cmd);
int						pathnnul(int valid, char *path, char *cmd, t_set *set);
int						ft_strcmpss(char *s1, char *s2);
int						is_dir_presentsl(char *arg, char *cmd);
int						exec_bin(t_set *set, char *path, char *cmd);
void					get_lastcmd(t_set *set);
char					*get_path(t_set *set, char *path, char *cmd);
char					*get_path_chemin(t_set *set, char *path, int len,
char *cmd);
char					*cmd_in_pwd(t_set *set, char *cmd);
int						ft_strlenbc(char *str);
int						check_sh(t_set *set, char *path);
int						check_stat_file(t_set *set, char *path);
char					**new_args(char **args, char *cmd);
int						ft_strcmpsl(char *s1, char *s2);
int						bash_cmd(t_set *set);
int						check_shlvl(t_set *set, char **envp);
int						ft_strcmp(char *s1, char *s2);

int						init_all(t_set *set, char **envp);
int						free_all(t_set *set, int ret);
void					disp_prompt(void);

char					*get_val(t_set *set);
void					sig_quit(int code);
int						ctrl_c(char *buf, t_set *set);
int						ft_dell2(t_set *set);
int						all_ccmd2(char *buf, t_set *set);

char					*wildcard(char *src, t_set *set);
int						is_wild(char *str);
char					**found_file(char *dst, char *wild, t_set *set);
int						correct_patern(char *file, char *wild, t_set *set);
void					ft_sort_file(char **dbtab);
char					*process_file(t_set *set, char *res, char **wild_splitted, char *pwd);
int						set_word(char *src, int i, t_set *set);
void					create_stdin(char *namefile, t_set *set);

#endif
