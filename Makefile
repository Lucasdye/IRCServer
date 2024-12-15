# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 16:46:22 by aboulest          #+#    #+#              #
#    Updated: 2024/05/02 18:10:09 by lbouguet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= ircserv

CC			:= c++
FLAGS		:= -Wall -Wextra -Werror -MMD -std=c++98 -g3

SRC			:= 	main.cpp			\
				IRC.cpp				\
				client.cpp			\
				channel.cpp			\
				capLS.cpp			\
				pass.cpp			\
				nick.cpp			\
				user.cpp			\
				ping.cpp			\
				join.cpp			\
				part.cpp			\
				privmsg.cpp			\
				topic.cpp			\
				mode.cpp			\
				whois.cpp			\
				kick.cpp			\
				quit.cpp			\
				invite.cpp			\
				

OBJ_DIR 	:= ./objs/
C_OBJ_DIR	:= @mkdir -p $(OBJ_DIR)
OBJ			:=$(SRC:.cpp=.o)
OBJ			:=$(addprefix $(OBJ_DIR), $(OBJ))

DEPS		:=$(OBJ:.o=.d)

###########################################################

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: %.cpp $(HEADER)
	$(C_OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

debug: FLAGS += -D DEBUG
debug: re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re

-include $(DEPS)
