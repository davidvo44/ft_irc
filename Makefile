# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 12:05:22 by saperrie          #+#    #+#              #
#    Updated: 2025/02/24 12:33:13 by saperrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

INCLUDE_DIR = headers/

CFLAGS = -Wall -Wextra -Werror -std=c++98
IFLAGS = -I$(INCLUDE_DIR)
DFLAGS = -MD -MP

OBJECT_DIR = .obj/

OBJECTS = $(patsubst %.cpp,$(OBJECT_DIR)%.o,\
		srcs/Client.cpp \
		srcs/Server.cpp \
		srcs/main.cpp \
		srcs/Poll.cpp \
		srcs/Commands/Command.cpp \
		srcs/ExceptionError.cpp \
		srcs/Channel.cpp \
		srcs/Message.cpp \
		srcs/Commands/Join.cpp \
		srcs/Commands/PrivMsg.cpp \
		srcs/Commands/Quit.cpp \
		srcs/Commands/Who.cpp \
		srcs/Commands/Nick.cpp \
		srcs/Commands/Part.cpp \
		srcs/Commands/Topic.cpp \
		srcs/Commands/Kick.cpp \
		srcs/Commands/Mode.cpp \
		srcs/RplMessage.cpp \
		)

OBJ_SUBDIRS = $(sort $(dir ${OBJECTS}))

DEPENDENCIES = $(OBJECTS:.o=.d)

NAME = ircserv

.PHONY: all
all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS)

$(OBJECT_DIR)%.o: %.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p ${OBJ_SUBDIRS}

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean
	@make --no-print-directory all
