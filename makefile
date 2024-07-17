# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 16:42:33 by szerzeri          #+#    #+#              #
#    Updated: 2024/07/17 16:56:31 by szerzeri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILENAMES = main.c\
get_env.c\
read_input.c\
input_error.c\
input_error1.c\
utils.c\
utils_1.c\
expander.c\
expander_utils.c\
free_functions.c\
free_functions1.c\
ft_split_new.c\
ft_split_new_utils.c\
tokenizer.c\
tokenizer_utils.c\
tokenizer_utils1.c\
tokenizer_utils2.c\
quotes_deleter.c\
heredoc.c\
input_redirections.c\
join_input_pipe.c\
output_redirections.c\
prepare_redirections.c\
prepare_cmd.c\
executor.c\
executor_utils.c\
executor_utils_1.c\
executor_onecmd.c\
executor_onecmd_util.c\
executor_inredir.c\
executor_outredir.c\
env_to_double.c\
error_msg.c\
signals.c\
./builtins/cd_builtin.c\
./builtins/echo_builtin.c\
./builtins/env_builtin.c\
./builtins/export_builtin.c\
./builtins/pwd_builtin.c\
./builtins/unset_builtin.c\
./builtins/exit_builtin.c\

LIBNAMES = ./libft/libft.a

LIBFT = ./libft/

CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -DUSERNAME=\"$(shell whoami)\" -DHOSTNAME=\"$(shell hostname)\"
CC = cc

OBJS	:=${FILENAMES:.c=.o}

$(NAME): $(OBJS)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(CPPFLAGS) $(FILENAMES) $(LIBNAMES) -o $(NAME) -lreadline
		@clear

all: $(NAME)

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJS)

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re