NAME = ft_IRC

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

IFLAGS = ./srcs/Client/Client.hpp \
			./srcs/Server/Server.hpp \
			./srcs/Poll/Poll.hpp \
			./srcs/Join/Join.hpp \
			./srcs/ExceptionError/ExceptionError.hpp \
			./srcs/Channel/Channel.hpp


SRCS = ./srcs/Client/Client.cpp \
	./srcs/Server/Server.cpp \
	./srcs/main.cpp \
	./srcs/Poll/Poll.cpp \
	./srcs/Join/Join.cpp \
	./srcs/ExceptionError/ExceptionError.cpp \
	./srcs/Channel/Channel.cpp

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
