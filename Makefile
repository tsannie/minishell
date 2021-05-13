# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 13:03:05 by tsannie           #+#    #+#              #
#    Updated: 2021/05/13 12:45:15 by tsannie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################################################
#                            Informations                            #
######################################################################

NAME			= minishell
CC				= @gcc
CFLAGS			= -Wall -Wextra -Werror #-fsanitize=leak
LIB_FLAGS		= -lncurses -lft -Llibft
RM				= @rm -rf
LIBFT			= ./libft
INCLUDE			= -I /minishell_basic/includes
INCLUDE_B		= -I /minishell_bonus/includes
INCLUDE_LIB		= -I ./libft/libft.a

#/bin/../../../bin/ls
#/bin//////////bin/ls
#/bin///////////ls




#/bin/Ls
#export A export A="qwe " export A
#ᴍɪɴɪsʜᴇʟʟ ➔  .
#ᴍɪɴɪsʜᴇʟʟ ➔  ..
#ᴍɪɴɪsʜᴇʟʟ ➔  exit

#leak
#cat Makefile > test

#bog
#Paste in minishell bonus


######################################################################
#                               C0l0r$                               #
######################################################################

BLACK			:= $(shell tput -Txterm setaf 0)
RED				:= $(shell tput -Txterm setaf 1)
GREEN			:= $(shell tput -Txterm setaf 2)
YELLOW			:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE		:= $(shell tput -Txterm setaf 4)
PURPLE			:= $(shell tput -Txterm setaf 5)
BLUE			:= $(shell tput -Txterm setaf 6)
WHITE			:= $(shell tput -Txterm setaf 7)
BOLD			:= $(shell tput -Txterm bold)
END				:= $(shell tput -Txterm sgr0)
NAMEC			= ${BLUE}${BOLD}$(NAME)${END}

######################################################################
#                            Source Files                            #
######################################################################

BIN			= binlib2.c binlib.c bin3.c bin2.c bin.c

TERMCAP		= term.c tgent.c mouv.c history.c tool.c

PARSING		= search_arg.c split_semicolon.c ft_dolars1.c ft_dolars2.c \
			ft_parsing_pipe.c search_cmd.c

CHECK		= ft_correct1.c ft_correct2.c ft_correct3.c ft_correct_pipe.c

BUILTIN_CMD	= ft_cd.c ft_echo.c ft_env.c exportpe.c ft_export.c ft_solo_export.c \
			ft_export_lib.c ft_exit.c ft_check_exit.c ft_unset.c ft_pwd.c

REDIRECT	= ft_redirection.c pipe.c ft_err_fold.c ft_namefile1.c ft_namefile2.c \
			ft_err_redi.c

MAIN		= main.c init.c start_sh.c err_msg.c ft_treat_cmd.c ft_init_env.c shlvl.c lib.c \
			 lib2.c lib3.c ft_splitbc.c ffree.c

SRC				= $(addprefix minishell_basic/srcs/bin/, $(BIN)) \
				$(addprefix minishell_basic/srcs/termcap/, $(TERMCAP)) \
				$(addprefix minishell_basic/srcs/builtin_cmd/, $(BUILTIN_CMD)) \
				$(addprefix minishell_basic/srcs/parsing/, $(PARSING)) \
				$(addprefix minishell_basic/srcs/main/, $(MAIN)) \
				$(addprefix minishell_basic/srcs/redirect/, $(REDIRECT)) \
				$(addprefix minishell_basic/srcs/check/, $(CHECK))

######################################################################
#                         Source Files_bonus                         #
######################################################################

BONUS			= edit_line_bonus.c edit_line2_bonus.c edit_copy_bonus.c \
				dell_bonus.c term_lib_bonus.c ft_redirect_bonus1.c \
				ft_redirect_bonus2.c wildcard_bonus1.c wildcard_bonus2.c \
				wildcard_bonus3.c

SRC_B			= $(addprefix minishell_bonus/srcs/bin/, $(BIN)) \
				$(addprefix minishell_bonus/srcs/termcap/, $(TERMCAP)) \
				$(addprefix minishell_bonus/srcs/builtin_cmd/, $(BUILTIN_CMD)) \
				$(addprefix minishell_bonus/srcs/parsing/, $(PARSING)) \
				$(addprefix minishell_bonus/srcs/main/, $(MAIN)) \
				$(addprefix minishell_bonus/srcs/redirect/, $(REDIRECT)) \
				$(addprefix minishell_bonus/srcs/check/, $(CHECK)) \
				$(addprefix minishell_bonus/srcs/bonus/, $(BONUS))

######################################################################
#                            Object Files                            #
######################################################################

OBJ				= $(SRC:c=o)

OBJ_B			= $(SRC_B:c=o)

######################################################################
#                               Rules                                #
######################################################################

norm:
			norminette libft/*.c libft/*.h ${SRC} ${SRC_B} */*/*.h

%.o: %.c
			@printf "${PURPLE}${BOLD}%-50.50s\r${END}" $@
			${CC} ${CFLAGS} -c $< -o $@

all:
			@printf "${PURPLE}${BOLD}Start compile ...\n${END}"
			@$(MAKE) $(NAME)

bonus:
			@printf "${PURPLE}${BOLD}Start compile ...\n${END}"
			@$(MAKE) c_bonus

$(NAME): 	$(OBJ)
			@echo "\n"
			@$(MAKE) -C $(LIBFT)
			$(CC) $(CFLAGS) -lft -ltermcap $(INCLUDE) $(INCLUDE_LIB) -o $(NAME) $(OBJ) $(LIB_FLAGS)
			@echo "\n${GREEN}The $(NAMEC) ${GREEN}has been build !${END}\n"

c_bonus:	$(OBJ_B)
			@echo "\n"
			@$(MAKE) -C $(LIBFT)
			$(CC) $(CFLAGS) -lft -ltermcap $(INCLUDE_B) $(INCLUDE_LIB) -o $(NAME) $(OBJ_B) $(LIB_FLAGS)
			@echo "\n${GREEN}The $(NAMEC) ${GREEN}has been build" \
				"(with ${BOLD}${WHITE}bonus${END}${GREEN}) !${END}"

clean:
			$(RM) $(OBJ) $(OBJ_B)
			@$(MAKE) clean -C $(LIBFT)
			@echo "${LIGHTPURPLE}Cleaning ...${END}\n"

fclean:		clean
			$(RM) $(NAME)
			@$(MAKE) fclean -C $(LIBFT)
			@echo "${LIGHTPURPLE}Delete $(NAMEC)${LIGHTPURPLE}...${END}\n"

re:			fclean all

.PHONY:		all test clean fclean re
