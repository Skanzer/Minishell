# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szerzeri <szerzeri@42berlin.student.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 16:42:33 by szerzeri          #+#    #+#              #
#    Updated: 2024/04/01 15:10:17 by szerzeri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILENAMES = main.c\
get_env.c\
read_input.c\
input_error.c\
utils.c\
expander.c\
expander_utils.c\

LIBNAMES = ./libft/libft.a

LIBFT = ./libft/

CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -DUSERNAME=\"$(shell whoami)\" -DHOSTNAME=\"$(shell hostname)\"
CC = cc

OBJS	:=${FILENAMES:.c=.o}

$(NAME): $(OBJS)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(CPPFLAGS) $(FILENAMES) $(LIBNAMES) -o $(NAME) -lreadline

all: $(NAME)

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJS)

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re