/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:44:19 by szerzeri          #+#    #+#             */
/*   Updated: 2024/04/05 16:27:13 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//printf, strerror, perror:
#include <stdio.h>
#include <errno.h>
//malloc, free, getenv:
#include <stdlib.h>
//strerror, perror:
#include <string.h>
//opendir, readdir, closedir:
#include <dirent.h>
//tcsetattr, tcgetattr:
#include <termios.h>
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs:
#include <term.h>
//signal, sigaction, sigemptyset, sigaddset, kill, exit:
#include <signal.h>
//write, access, open, read, close, dup, dup2, pipe, isatty, ttyname, ttyslot, ioctl:
#include <unistd.h>
//getcwd, chdir, stat, lstat, fstat, unlink, execve:
#include <sys/stat.h>
//fork, wait, waitpid, wait3, wait4:
#include <sys/types.h>
#include <sys/wait.h>
//readline:
#include <readline/readline.h>
//rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history:
#include <readline/history.h>
//libft
#include "./libft/libft.h"

#define ANSI_RESET   "\x1B[0m"
#define ANSI_RED     "\x1B[31m"
#define ANSI_GREEN   "\x1B[32m"
#define ANSI_YELLOW  "\x1B[33m"
#define ANSI_BLUE    "\x1B[34m"
#define ANSI_MAGENTA "\x1B[35m"
#define ANSI_CYAN    "\x1B[36m"
#define ANSI_WHITE   "\x1B[37m"

# define SUCCESS 0
# define INPUT_ERROR 1
# define ALLOC_ERROR 2

typedef enum e_token_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
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
	struct s_quotes		*next;
}	t_tokens;

typedef struct s_commands
{
	char				*command;
	t_tokens			*tokens;
	struct s_commands	*next;
}	t_commands;

typedef struct s_minishell
{
	t_env				*env;
	char				*input;
	t_commands			*commands;
}	t_minishell;

/////////////get_env.c//////////////////////////////////////////////
int					get_env(t_minishell *mini, char **env);
/////////////read_input.c//////////////////////////////////////////////
char				*read_input(void);
/////////////utils.c//////////////////////////////////////////////
int					quotes(char *input, int i);
unsigned int		ft_strcpy(char *dest, const char *src);
/////////////input_error.c//////////////////////////////////////////////
int					error_check(char *input);
////////////expander.c////////////////////////////////////////////////
char				*input_expansion(char *input, t_env *env);
char				*insert_var(char *input, int i, char *value, char *name);
void 				skip_single_quotes(char *input, int *i);
char				*get_var_value(char *var, t_env *env);
/////////////free_functions.c//////////////////////////////////////////////
void				free_env(t_minishell *minishell);
void				free_double(char **array, int i);
void    			free_commands(t_minishell *minishell);
void    			free_shell(t_minishell *minishell);
/////////////ft_split_new.c//////////////////////////////////////////////
char				**ft_split_new(char const *str, char c);
int					ft_wordcount(char *str, char c);
void				ft_wordcount_util(char *str, int *i);
void 				ft_stralloc_util(char *str, int *k, int *i);
/////////////tokenizer.c//////////////////////////////////////////////////
int					tokenizer(t_minishell *mini);
#endif