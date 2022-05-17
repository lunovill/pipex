# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lunovill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 13:54:26 by lunovill          #+#    #+#              #
#    Updated: 2022/05/16 21:41:04 by lunovill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #=============================================================================#
#								SOURCES											#
 #=============================================================================#

SRCS_DIR = sources
SRC_FILES =	chk_args\
		ft_error\
		ft_path\
		ft_ppsplit\
		main\
		pid_child\
		pid_father\
		pipex\

SRCS = $(addsuffix .c, $(SRC_FILES))

SRC_FILES_BONUS = $(addsuffix _bonus, $(SRC_FILES))
SRCS_BONUS = $(addsuffix .c, $(SRC_FILES_BONUS))

 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objets
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIBS_DIR = libft
LIBS = libft.a

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CIFLAGS = -Iincludes -I$(LIBS_DIR)/includes
CLFLAGS = -L$(LIBS_DIR) -lft

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = pipex
NAME_BONUS = pipex_bonus

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(MAKE) -C $(LIBS_DIR)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) -o $(NAME)

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(CIFLAGS) -c $< -o $@

bonus : $(OBJS_DIR) $(BONUS)
	$(MAKE) -C $(LIBS_DIR)
	$(CC) $(CFLAGS) $(CIFLAGS) $(BONUS) $(CLFLAGS) -o $(NAME_BONUS)

$(BONUS) : $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIBS_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBS_DIR)
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
re : fclean all

.PHONY: clean fclean all re
