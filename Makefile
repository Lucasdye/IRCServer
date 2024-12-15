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
CPP_DIR		:= ./srcs/cpp/
OBJ_DIR 	:= ./objs/
CC			:= c++
FLAGS		:= -Wall -Wextra -Werror -MMD -std=c++98 -g3

CPP_FILES		:= 	main.cpp		\
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

CREATE_OBJ_DIR	:= @mkdir -p $(OBJ_DIR)
OBJ_FILES		:=$(CPP_FILES:.cpp=.o)
SRC_CPP			:= $(addprefix $(CPP_DIR), $(CPP_FILES))
OBJ				:=$(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEPS			:=$(OBJ:.o=.d)


###########################################################

all: $(NAME)

$(NAME): $(OBJ) 
	@echo $(OBJ)
	@echo "Targetting NAME"
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(CPP_DIR)%.cpp
	@echo "Creating obj directory"
	$(CREATE_OBJ_DIR)
	@echo "Targetting $(OBJ_DIR).o file"
	$(CC) -c $< -o $@
	
clean:
	rm -rf ./objs/

fclean: clean
	rm $(NAME)

.PHONY : all clean fclean re

-include $(DEPS)
