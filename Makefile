# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:00:45 by tsannie           #+#    #+#              #
#    Updated: 2021/02/17 09:27:46 by tsannie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= @gcc
CFLAGS		= #-Wall -Wextra -Werror

RM			= @rm -rf
LIBFT		= ./libft

BLACK		:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
BOLD		:=$(shell tput -Txterm bold)
END			:= $(shell tput -Txterm sgr0)
NAMEC		= ${BLUE}${BOLD}$(NAME)${END}
NAMELIB		= ${BLUE}${BOLD}Libft${END}

SRC			= main.c start_sh.c ft_cd.c ft_echo.c ft_env.c ft_export.c \
ft_unset.c ft_pwd.c ft_treat_cmd.c search_arg.c ft_solo_export.c ft_exit.c \
split_semicolon.c ft_dolars.c tools_dev_DELETE.c \



SRC_BONUS 	= \

OBJ			= $(addprefix minishell_basic/srcs/, $(SRC:.c=.o))
OBJ_BONUS	= $(addprefix srcs/, $(SRC_BONUS:.c=.o))

all:		$(NAME)

$(NAME): 	$(OBJ)
			@echo "${YELLOW}${BOLD}Start compile ...${END}"
			@$(MAKE) -C $(LIBFT)
			@echo "${GREEN}The $(NAMELIB) ${GREEN}has been build !${END}"
			$(CC) $(CFLAGS) -I/minishell_basic/includes ./libft/libft.a -o $(NAME) $(OBJ)
			@echo "${GREEN}The $(NAMEC) ${GREEN}has been build !${END}"

clean:
			$(RM) $(OBJ)
			@$(MAKE) clean -C $(LIBFT)
			@echo "${PURPLE}Cleaning ...${END}"

fclean:		clean
			$(RM) $(NAME)
			@$(MAKE) fclean -C $(LIBFT)
			@echo "${PURPLE}Delete $(NAMEC)${PURPLE}...${END}"

test:		re
			@make clean
			./$(NAME)
			@echo "\n"

re:			fclean all

.PHONY:		all test clean fclean re