NAME = ircserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g 

IFLAGS = ./srcs/Client/Client.hpp \
			./srcs/Server/Server.hpp \
			./srcs/Poll/Poll.hpp \
			./srcs/Command/Command.hpp \
			./srcs/ExceptionError/ExceptionError.hpp \
			./srcs/Channel/Channel.hpp \
			./srcs/Message/Message.hpp \
			./srcs/RplMessage/RplMessage.hpp


SRCS = ./srcs/Client/Client.cpp \
	./srcs/Server/Server.cpp \
	./srcs/main.cpp \
	./srcs/Poll/Poll.cpp \
	./srcs/Command/Command.cpp \
	./srcs/ExceptionError/ExceptionError.cpp \
	./srcs/Channel/Channel.cpp \
	./srcs/Message/Message.cpp \
	./srcs/Command/Join.cpp \
	./srcs/Command/PrivMsg.cpp \
	./srcs/Command/Quit.cpp \
	./srcs/Command/Who.cpp \
	./srcs/Command/Nick.cpp \
	./srcs/Command/Part.cpp \
	./srcs/Command/Topic.cpp \
	./srcs/Command/Kick.cpp \
	./srcs/Command/Mode.cpp \
	./srcs/RplMessage/RplMessage.cpp

DIR_OBJ := .object/

OBJS = $(patsubst %.cpp, ${DIR_OBJ}%.o, ${SRCS})

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)


${DIR_OBJ}%.o: %.cpp $(IFLAGS) Makefile
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
