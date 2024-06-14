/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:44:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/06/14 21:37:56 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//printf, strerror, perror:
# include <stdio.h>
# include <errno.h>
//malloc, free, getenv:
# include <stdlib.h>
//strerror, perror:
# include <string.h>
//opendir, readdir, closedir:
# include <dirent.h>
//tcsetattr, tcgetattr:
# include <termios.h>
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs:
# include <term.h>
//signal, sigaction, sigemptyset, sigaddset, kill, exit:
# include <signal.h>
//write, access, open, read, close, dup, dup2, pipe, isatty, ttyname, ttyslot, ioctl:
# include <fcntl.h>
# include <unistd.h>
//getcwd, chdir, stat, lstat, fstat, unlink, execve:
# include <sys/stat.h>
//fork, wait, waitpid, wait3, wait4:
# include <sys/types.h>
# include <sys/wait.h>
//readline:
# include <readline/readline.h>
//rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history:
# include <readline/history.h>
//libft
# include "./libft/libft.h"

# define ANSI_RESET   "\x1B[0m"
# define ANSI_RED     "\x1B[31m"
# define ANSI_GREEN   "\x1B[32m"
# define ANSI_YELLOW  "\x1B[33m"
# define ANSI_BLUE    "\x1B[34m"
# define ANSI_MAGENTA "\x1B[35m"
# define ANSI_CYAN    "\x1B[36m"
# define ANSI_WHITE   "\x1B[37m"

# define SUCCESS 0
# define INPUT_ERROR 1
# define ALLOC_ERROR 2

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# define PATH_MAX 4096

# define WRITE 1
# define READ 0

typedef enum e_token_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_tokens
{
	char				*token;
	t_token_type		type;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_commands
{
	t_env				*env;
	char				*command;
	t_tokens			*tokens;
	char				*builtin;
	char				*cmd_path;
	char				**cmd_args;
	char				*infile;
	int					infile_fd;
	char				*outfile;
	char				*append;
	int					outfile_fd;
	char				*heredoc;
	int					quoted_heredoc;
	int					index;
	struct s_commands	*next;
}	t_commands;

typedef struct s_minishell
{
	t_env				*env;
	char				*input;
	t_commands			*commands;
	int					**pipe_fd;
	char				*pwd;
	char				*old_pwd;
	size_t				exit_status;
	pid_t				pid;
	int					index_cmd;
	int					nb_cmd;
}	t_minishell;

typedef struct s_string
{
	char				c;
	struct s_string		*next;
	struct s_string		*previous;
}	t_string;

/////////////get_env.c//////////////////////////////////////////////
int					get_env(t_minishell *mini, char **env);
/////////////read_input.c//////////////////////////////////////////////
char				*read_input(void);
/////////////utils.c//////////////////////////////////////////////
int					quotes(char *input, int i);
unsigned int		ft_strcpy(char *dest, const char *src);
int					end_var_name(char c);
int					space_char(char c);
t_tokens			*delete_token_node(t_tokens *tokens, t_token_type type);
t_tokens			*find_token(t_tokens *token, t_token_type type);
int					open_file(char *file_name, int w_r);
/////////////input_error.c//////////////////////////////////////////////
int					error_check(char *input);
int					redirection_error(char *input);
int					after_redir_check(t_commands *commands);
int					empty_input(char *input);
////////////expander.c////////////////////////////////////////////////
int					input_expansion(char *input, t_env *env);
char				*insert_var(char *input, int i, char *value, char *name);
void				skip_single_quotes(char *input, int *i);
char				*get_var_value(char *var, t_env *env);
/////////////free_functions.c//////////////////////////////////////////////
void				free_env(t_minishell *minishell);
void				free_double(char **array);
void				free_commands(t_commands *commands);
void				free_shell(t_minishell *minishell);
void				free_string(t_string *string);
void				free_tokens(t_tokens *tokens);
/////////////ft_split_new.c//////////////////////////////////////////////
char				**ft_split_new(char const *str, char *c);
int					ft_wordcount(char *str, char *c);
void				ft_wordcount_util(char *str, int *i);
void				ft_stralloc_util(char *str, int *k, int *i);
int					check_c(char c, char *characters);
/////////////tokenizer.c////////////////////////////////////////////////////
int					tokenizer(t_minishell *mini);
int					organize_commands(t_commands *commands);
int					replace_command(t_commands *commands, t_string *string);
int					create_tokens(t_commands *commands);
/////////////quotes_deleter.c///////////////////////////////////////////////
int					quotes_deleter_all(t_commands *commands);
int					quotes_deleter(t_tokens *tokens);
char				*copy_without_quotes(char *token, char *new_token);
//////////////heredoc.c//////////////////////////////////////////////////////
int					heredoc(t_commands *commands);
//////////////input_redirections.c///////////////////////////////////////////
int					input_redir(t_commands *commands);
//////////////join_input_pipe.c//////////////////////////////////////////////
int					join_input_pipe(char *input);
//////////////output_redirections.c//////////////////////////////////////////
int					output_redir(t_commands *commands);
int					append_redir(t_commands *commands);
//////////////prepare_redirections.c/////////////////////////////////////////
int					in_app_out_redir(t_commands *commands);
void				last_redir(t_commands *commands);
//////////////prepare_cmd.c//////////////////////////////////////////////////
int					create_cmd_args(t_commands *commands);
//////////////executor.c/////////////////////////////////////////////////////
int					execute_one_cmd(t_minishell *minishell, char **env);
int					executor(t_minishell *minishell);
int					**create_pipe_fd(t_minishell *minishell);
void				free_pipe(t_minishell *mini, int **array);
int					count_cmds(t_commands *commands);
void				close_pipe_fd(t_minishell *minishell);
void				dup_pipefd(t_minishell *minishell, t_commands *cmd);
int					dup_infile(t_minishell *minishell, t_commands *cmd);
int					dup_heredoc(t_minishell *minishell, t_commands *cmd);
int					dup_in_redir(t_minishell *minishell, t_commands *cmd);
int					dup_out_redir(t_minishell *minishell, t_commands *cmd);
void				cmd_execution(t_commands *command, char **env);
//////////////env_to_double.c////////////////////////////////////////////////
char				**env_double(t_env *env);
//////////////error_msg.c////////////////////////////////////////////////////
int 				error_msg(char *cmd, char *msg, int error_nb);

#endif