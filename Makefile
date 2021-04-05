# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:00:45 by tsannie           #+#    #+#              #
#    Updated: 2021/04/01 16:53:04 by phbarrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= @gcc

CFLAGS		= #-Wall -Wextra -Werror #-fsanitize=leak

#whaomi
#wHoami
#/bin/../../../bin/ls
#/bin//////////bin/ls
#/bin/Ls
#export A export A="qwe " export A


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
BOLD		:= $(shell tput -Txterm bold)
END			:= $(shell tput -Txterm sgr0)
NAMEC		= ${BLUE}${BOLD}$(NAME)${END}

BIN			= binlib2.c binlib.c bin3.c bin2.c bin.c

TERMCAP		= term.c

PARSING		= search_arg.c split_semicolon.c ft_dolars1.c ft_dolars2.c

CHECK		= ft_correct1.c ft_correct2.c ft_correct3.c

BUILTIN_CMD	= ft_cd.c ft_echo.c ft_env.c exportpe.c ft_export.c ft_solo_export.c \
			ft_export_lib.c ft_exit.c ft_check_exit.c ft_unset.c ft_pwd.c

REDIRECT	= ft_redirection.c pipe.c ft_err_fold.c

MAIN		= main.c init.c start_sh.c err_msg.c ft_treat_cmd.c ft_init_env.c shlvl.c lib.c \
			 lib2.c lib3.c ft_splitbc.c tgent.c get_next_line.c tools_dev_DELETE.c ffree.c

SRC			= $(addprefix minishell_basic/srcs/bin/, $(BIN)) \
			$(addprefix minishell_basic/srcs/termcap/, $(TERMCAP)) \
			$(addprefix minishell_basic/srcs/builtin_cmd/, $(BUILTIN_CMD)) \
			$(addprefix minishell_basic/srcs/parsing/, $(PARSING)) \
			$(addprefix minishell_basic/srcs/main/, $(MAIN)) \
			$(addprefix minishell_basic/srcs/redirect/, $(REDIRECT)) \
			$(addprefix minishell_basic/srcs/check/, $(CHECK))

OBJ			= $(SRC:c=o)

#OBJ_BONUS	= $(addprefix srcs/, $(SRC_BONUS:.c=.o))

%.o: %.c
			@printf "${PURPLE}${BOLD}Start compile ... %-50.50s\r${END}" $@
			${CC} ${CFLAGS} -c $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@echo "\n"
			@$(MAKE) -C $(LIBFT)
			$(CC) $(CFLAGS) -I/minishell_basic/includes ./libft/libft.a -o $(NAME) $(OBJ) -lncurses -lft -Llibft
			@echo "\n${GREEN}The $(NAMEC) ${GREEN}has been build !${END}\n"

clean:
			$(RM) $(OBJ)
			@$(MAKE) clean -C $(LIBFT)
			@echo "${LIGHTPURPLE}Cleaning ...${END}\n"

fclean:		clean
			$(RM) $(NAME)
			@$(MAKE) fclean -C $(LIBFT)
			@echo "${LIGHTPURPLE}Delete $(NAMEC)${LIGHTPURPLE}...${END}\n"

re:			fclean all

.PHONY:		all test clean fclean re