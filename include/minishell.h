/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:44:18 by msulc             #+#    #+#             */
/*   Updated: 2023/09/14 16:39:39 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# include <errno.h>
# include "../libft/libft.h"

//#define MAX_LINE 1024
# define TRUE 1
# define FALSE 0

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

typedef struct s_elem		t_elem;
typedef struct s_redir_elem	t_redir_elem;
typedef union u_union		t_union;
typedef struct s_pipe		t_pipe;
typedef struct s_redir_list	t_redir_list;

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	t_elem			*next;
	t_elem			*prev;
}	t_elem;

typedef struct s_list_n
{
	t_elem	*head;
	t_elem	*tail;
	int		size;
}	t_list_n;

typedef struct s_node_cmd
{
	char				*path;
	char				**cmd;
	char				*redir_in;
	char				*in_name;
	int					in_fd;
	char				*redir_out;
	char				*out_name;
	int					out_fd;
	struct s_node_cmd	*next;
}				t_node_cmd;

typedef struct s_node
{
	char			*key;
	char			eq;
	char			*value;
	struct s_node	*next;
}		t_node;

typedef struct s_data
{
	char		**path;
	char		*line;
	int			nbrofcom;
	int			nbr_pipes;
	int			*fd_pipes;
	char		*prompt;
	char		*home;
	char		*old_cwd;
	int			exitstatus;
	t_node		*enviro;
	t_list_n	*lex;
	t_node_cmd	*cmds;
}	t_data;

//fd_close.c
void		ft_close_two_fd(int *fd1, int *fd2);
void		ft_close_pipes(t_data *mini);

//fd_create.c
int			create_pipes(t_data	*mini);
void		open_redirs(t_data *mini);

//executor.c
void		ft_executor(t_data	*mini, char **envp);

//signals.c
void		sig_handl_child(int sig);
void		ft_signal_handler(int signal);

//errors.c
void		ft_strerror(char *msg, char *name);
int			ft_perror(char *msg, char *utils);

//ft_execve.c
void		ft_execve(t_node_cmd *node, t_data *mini, char **env);

//child_execute.c
int			execute_cmd(t_node_cmd *node, t_data *mini, char **env);
int			heredoc_function(t_node_cmd *node);
int			ft_waitpid(pid_t pid);

//builtins1.c
int			ft_unset(t_data *mini, t_node_cmd *cmd);
int			ft_export(t_data *mini, t_node_cmd *cmd);
int			ft_cd(t_data *mini, t_node_cmd *cmd);
int			ft_exit(t_data *mini, t_node_cmd *cmd);

//builtins2.c
int			ft_is_builtin(char *str);
int			ft_execute_builtin(t_data *mini, t_node_cmd *cmd);
char		*dot_ext(char *pcwd, t_node_cmd *cmd);

//builtins_output.c
int			is_builtin_with_output(char *str);
void		ft_execute_fork_builtin(t_data *mini, t_node_cmd *cmd);
void		ft_env(t_data *mini);
void		ft_pwd(t_node_cmd *cmd);
int			ft_echo(t_node_cmd *cmd);

//builtins_utils.c
void		ft_update_cwd(t_data *mini, char *cwd, char *pcwd);
int			check_env_var_and_repl(t_node **head, t_node_cmd *cmd);
char		*get_arg_cd_ext(char *home, char *pcwd, t_node_cmd *cmd, char c);
char		*get_arg_cd(t_node_cmd *cmd, char *home, char *old_cwd, char *pcwd);
int			ft_isnum(char *arg);

//	lexer_utils1.c
char		*ft_strndup(char *s1, int n);
int			ft_isspace(char c);
int			is_alphanum(int c);
int			in_charset(char c);
void		quotes_state(t_list_n *tokens, char *str, \
							enum e_state *state, int flag);

//	lexer_utils2.c
int			pipe_err(t_elem *el);
int			redir_err(t_elem *ptr);
t_elem		*quotes_err(t_elem **ptr, enum e_token type);
char		*get_redir_symb(enum e_token type);
int			sintax_check(t_list_n *list);

//	lexer_utils3.c
t_elem		*skip_space(t_elem *ptr, int opt);
int			is_redir(enum e_token type);

//	lexer_list.c
int			is_empty(t_list_n *list);
t_list_n	*init_list(t_list_n *list);
t_elem		*new_elem(char *content, int len, enum e_token type, \
						enum e_state state);
void		add_tail(t_list_n *list, t_elem *new);
void		free_list(t_list_n *list);

//	lexer.c
int			get_word(t_list_n *tokens, char *str, enum e_state state);
int			get_env_token(t_list_n *tokens, char *str, enum e_state state);
int			make_token_redir(t_list_n *tokens, char *str, \
								int idx, enum e_state state);
int			ft_make_token(t_list_n *tokens, char *str, int i, \
								enum e_state *state);
t_list_n	*lexer(char *line);

//	parser_utils2.c
void		count_quotes_redir_args(t_elem **elem, enum e_token type, int *i);
int			count_args(t_elem *elem);
int			get_pipe_nbr(t_list_n *list);
int			is_full(char *str);
void		abs_path_check(t_node_cmd **head);

//	parser_utils1.c
char		*get_env(t_node *env, char *key);
void		parse_env(t_elem **elem, char **args, int *i, t_data *mini);
char		*parse_quo(char *line, t_elem **node, \
						enum e_token type, t_data *mini);

//	parser.c
void		parse_word(t_elem **elem, char **args, int *i);
char		*get_name(t_elem **node, t_data *mini);
void		check_redir(t_node_cmd *new, enum e_token type);
void		parse_redir(t_elem **node, t_data *mini, t_node_cmd	*new);
t_node_cmd	*parsing(t_list_n *list, t_data *mini);

//	cmd_list.c
void		ft_add_cmd_end(t_node_cmd **head, t_node_cmd *new);
t_node_cmd	*new_cmd_node_init(int size, int *i);
t_node_cmd	*new_cmd_node(t_elem **list, int size, t_data *mini);
void		remove_cmd_list(t_node_cmd **head);

//minishell_utils.c
void		ft_data_init(t_data *mini, char **envp);
void		ft_reset_values(t_data *mini);
void		ft_path_filler(t_data *mini);
int			ft_has_characters(char *line);

//	env_list.c
t_node		*create_env_list(char **env);
void		remove_env_list(t_node **head);
void		ft_add_end(t_node **head, char *env);
char		*ft_separate_key(char *env);
char		*ft_separate_value(char *env);

//	env_remove.c
void		ft_remove_node(t_node **head, char *key);

//	minishell.c
int			main(void);
int			ft_line(t_data *mini);
void		path_clean(t_data *mini);
void		ft_cleaning(t_data *mini);

#endif
