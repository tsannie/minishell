# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/11 08:07:49 by tsannie           #+#    #+#              #
#    Updated: 2021/03/29 15:17:48 by tsannie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= @gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= libft.h
RM			= @rm -rf

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

SRC			= ft_isdigit.c ft_memmove.c ft_strncmp.c ft_atoi.c ft_isprint.c \
ft_memset.c ft_strnstr.c ft_bzero.c ft_memccpy.c ft_strchr.c ft_strrchr.c \
ft_isalnum.c ft_memchr.c ft_strlcat.c ft_tolower.c ft_isalpha.c ft_memcmp.c \
ft_strlcpy.c ft_toupper.c ft_isascii.c ft_memcpy.c ft_strlen.c ft_strdup.c \
ft_calloc.c ft_split.c ft_rev_int_tab.c ft_rev_char_tab.c ft_itoa.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_strjoin.c \
ft_strmapi.c ft_strtrim.c ft_substr.c ft_putunbr_fd.c ft_putultoh.c \
ft_putuihex.c ft_nbcharint.c ft_nbcharhex.c ft_nbcharuint.c ft_lstnew.c \
ft_nbcharuihex.c ft_putstrn_fd.c ft_minvalue.c ft_maxvalue.c ft_putuihexm.c \
 ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstmap.c \
ft_lstadd_front.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
ft_iscolor.c ft_ispair.c ft_streql.c ft_iswhite.c ft_realloc.c ft_free_dbtab.c \
ft_istab.c

OBJ			= $(SRC:.c=.o)

OBJ			= $(SRC:.c=.o)

%.o: %.c
			@printf "${PURPLE}${BOLD}Start compile libft ... %-33.33s\r${END}" $@
			${CC} ${CFLAGS} -c $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@ranlib $(NAME)
			@echo "\n\n${GREEN}The $(NAMEC) ${GREEN}has been build !${END}"

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re