/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:00:46 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/13 15:12:21 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <bsd/string.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define INPUT 1    //
# define HERE_DOC 2 //   <<
# define CMD 3
# define ARG 4
# define PIPE 5          // PIPE
# define OUTPUT_APPEND 6 //   >>
# define OUTPUT_TRUNC 7  //   >

typedef struct s_token
{
	char			*str;
	int				str_malloc;
	int				type;
	char			*cmd;
	int				cmd_malloc;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_str;
	char			**full_cmd;
	int				count_here_doc;
	int				infile_here_doc;
	char			**limiters;
	int				limiters_malloc;
	int				full_cmd_malloc;
	int				path_check;
	char			**infile_tab;
	int				infile_tab_malloc;
	char			*infile;
	int				fail_infile;
	int				fail_outfile;
	int				infile_malloc;
	char			*outfile;
	char			**outfile_tab;
	int				outfile_tab_malloc;
	int				outfile_append_check;
	int				*outfile_append_check_tab;
	int				outfile_append_check_tab_malloc;
	char			*echo_arg;
	char			*next_arg;
	int				next_arg_type;
	int				echo_arg_malloc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipex
{
	t_cmd			*lst_cmd;
	int				lst_cmd_malloc;
	t_token			*lst_token;
	int				lst_token_malloc;
	int				cmd_size;
	int				exec_count;
	pid_t			*pid;
	int				pid_malloc;
	int				*pipefd;
	int				pipefd_malloc;
	char			**env;
	int				env_malloc;
	int				here_doc_check;
	char			**path_env;
	char			**variables_parsing;
	int				variables_parsing_malloc;
	int				compteur_characters;
	int				path_env_malloc;
	int				env_check;
	int				saved_stdin;
	int				saved_stdout;
	int				status;
	int				status_check;
	char			*first_path;
	int				first_path_malloc;
}					t_pipex;

char				*une_histoire_de_pipe(char *line);
void				ft_printf_pipex(t_pipex *pipex);
void				ft_print_lst_cmd(t_cmd *lst_cmd);
void				join7(char *line, char *buf, char *conc);
char				*ft_strjoin7(char *line, char *buf);
char				*ft_strchr8(const char *s, int c);
void				ft_print_lst_token(t_token *lst_token);
char				**ft_add_backslash(char **path);
char				**ft_path(char **env);
char				*get_next_line(int fd, char *limiter, t_pipex *pipex);
t_token				*lst_token_maker(char *line, t_pipex *pipex);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
void				ft_lstclear_token(t_token **lst);
t_token				*ft_lstlast_token(t_token *lst);
void				lst_token_put_back(t_token *lst_token);
t_token				*lst_token_maker2(char **tab_line);
int					ft_lstsize_token(t_token *lst);
t_cmd				*lst_cmd_maker(t_token *lst_token);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				ft_lstclear_cmd(t_cmd **lst);
int					init_pipex_struc(t_pipex *pipex, char **env, int ac,
						char **av);
int					get_here_doc_input_console(t_cmd *lst_cmd, t_pipex *pipex);
char				*get_here_doc_input(char *limiter, t_pipex *pipex);
void				liberator_god(t_pipex *pipex, int sup_all);
int					init_pipex_struc_cmd(t_pipex *pipex, char *line);
int					ft_lstsize_cmd(t_cmd *lst);
int					ft_strlen4(char *str);
char				*ft_strjoin5(char *s1, char *s2);
int					access_check(t_token *token, t_pipex *pipex);
int					life_fille(t_pipex *pipex, t_cmd *lst_cmd);
int					life_papa(t_pipex *pipex, t_cmd *lst_cmd);
int					call_pipex(t_pipex *pipex);
int					lst_cmd_init_here_doc(t_cmd *new, t_token *lst_token,
						char c);
int					set_signal_action(void);
void				ft_echo(t_cmd *lst_cmd);
void				ft_env(t_pipex *pipex);
char				*echo_arg(t_cmd *lst_cmd, t_token *lst_token, int i);
int					echo_valid_arg(char *str);
char				*parsing_pre_token(char *line, t_pipex *pipex);
void				ft_builtins(t_cmd *lst_cmd, t_pipex *pipex, char c);
void				malloc_fail(void);
void				export_fail(char *s);
void				liberator(char **s, int k);
void				ft_export(t_cmd *lst_cmd, t_pipex *pipex, int j, int i);
void				ft_unset(t_cmd *lst_cmd, t_pipex *pipex);
void				boucle_principale(t_pipex *pipex);
void				cmd_fail(t_pipex *pipex);
void				open_here_doc(t_pipex *pipex);
int					*tab_int_outfile(t_token *lst_token);
char				**tab_infile(t_token *lst_token);
char				**tab_outfile(t_token *lst_token);
void				open_infile_outfile(t_pipex *pipex);
void				ft_cd(t_cmd *lst_cmd, t_pipex *pipex);
void				join5(char *s1, char *s2, char *conc);
char				*ft_strjoin5(char *s1, char *s2);
int					call_pipex_cmd_unique(t_pipex *pipex);
int					open_infile(t_pipex *pipex, t_cmd *lst_cmd);
int					open_outfile(t_pipex *pipex, t_cmd *lst_cmd);
int					def_type_token(char *str, t_token *token);
int					def_empty_or_false_cmd_token(t_token *token);
int					check_outfile_append(t_token *lst_token);
char				*check_outfile_cmd(t_token *lst_token);
char				*check_infile_cmd(t_token *lst_token);
char				*parsing_pre_token(char *line, t_pipex *pipex);
char				*ft_parsing_dollars_without_brackets(char *line,
						t_pipex *pipex);
char				*get_part_with_brackets(char *line, int i);
int					check_line(char *line, int i);
char				*get_part_without_dollars2(char *line, int i);
int					check_next_quote(char *line, int ascii, int i);
int					ft_strlen_table(char **table);
int					char_is_ok(char c);
char				*search_env_get_variable(int i, int j, t_pipex *pipex,
						int format);
char				*get_part_without_dollars(char *line, int i);
char				**segmenting_line(char *line, int ascii, int i);
char				*double_quote_management(char *line, int i, int ascii,
						t_pipex *pipex);
char				**segmenting_brackets(char *line, t_pipex *pipex);
char				*search_env(char *line, t_pipex *pipex, int format);
void				read_fail(void);
void				ctrld_actioned(char *limiter);
void				creation_fail(void);
void				permission_fail(char *str);
int					path_check(char **env);
void				pipe_fail(void);
char				**create_env(void);
void				fork_fail(void);
void				perm_or_file_missing(char *str);
void				pre_init(t_pipex *pipex);
void				dup2_fail(void);
void				waitpid_fail(void);
void				mini_liberator(char *next_line, char *buf);
void				mini_liberator_exit(char *next_line, char *buf);
char				*replace_status(char *line, t_pipex *pipex);
int					is_in_brackets(char *line, int k);
char				*parsing_champetre(char *line, t_pipex *pipex);
char				**ft_strdup_table2(char **env);
void				les_espaces_cest_pas_cool(char *line);
void				open_files(t_pipex *pipex);
int					infile_outfile_count(t_token *lst_token, int indice);
int					ft_lstnew_cmd_init(t_cmd *new, t_token *lst_token);
char				**check_args_cmd(t_token *lst_token);
char				*fixe_variable(char *variable);
char				*replace_status2(char *line, char *error, int i);
char				*replace_status_get_last_part(int i, char *line);
char				*replace_status_get_first_part(int i, char *line);
char				*ft_copy_end(char *s, int start);
char				*ft_copy_start(char *s, int len);
char				*ft_rejoin_parts(char *first_part, char *error,
						char *end_part);
int					check_linked_token(t_token *token);
int					null_apres_un_truc(t_token *token);
int					trois_trucs_et_cest_foutu(char *line, char truc);
int					il_y_a_et_ciao(char *line);
char				*add_space(char *line, int i);
void				ft_cd1(t_pipex *pipex);
void				ft_cd2(t_pipex *pipex);
void				ft_cd3(t_pipex *pipex);
void				ft_cd4(t_pipex *pipex);
void				ft_cd5(t_pipex *pipex, t_cmd *lst_cmd);
char				*ft_home_path(char **env, char *path);
void				update_pwd(t_pipex *pipex);
char				*ft_get_home_path(char **env);
void				ft_petite_help2(int indice, t_pipex *pipex);
int					ft_indice(int indice, int *i, int *j);
int					ft_first_while(int *i, int k, int indice, t_cmd *lst_cmd);
void				ft_export_petite_la(t_pipex *pipex, t_cmd *lst_cmd, int k,
						int j);
int					petit_a_petit_fait_son_nid(int *j);
int					ft_strcmp(char *str1, char *str2);
char				**ft_copy_env_export(char **env, char *new_str);
void				ft_change_env_variable(t_pipex *pipex, char *str, int j);
void				liberator(char **s, int k);
void				ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *,
							char *));
int					ft_export2(t_cmd *lst_cmd, int i, int k, int indice);
int					ctrl_c_here_doc(t_pipex *pipex);
int					get_here_doc_false_input(t_cmd *lst_cmd, t_pipex *pipex);
int					set_signal_action1(void);

#endif
