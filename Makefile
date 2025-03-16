
CC = c++

INCLUDE_DIR = headers/

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
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
		srcs/Commands/Mode.cpp \
		srcs/Commands/Kick.cpp \
		srcs/Commands/Invite.cpp \
		srcs/Commands/Pass.cpp \
		srcs/Commands/User.cpp \
		srcs/Commands/SendClientSharedChannels.cpp \
		srcs/Commands/Chess.cpp \
		srcs/Bot.cpp \
		srcs/Chess/PieceCondition.cpp \
		srcs/Chess/MovePiece.cpp \
		srcs/Chess/ChessStart.cpp \
		srcs/Chess/ChessMainStruc.cpp \
		)

OBJ_SUBDIRS = $(sort $(dir ${OBJECTS}))

DEPENDENCIES = $(OBJECTS:.o=.d)

NAME = ircserv

.PHONY: all
all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS)

$(OBJECT_DIR)%.o: %.cpp Makefile | $(OBJECT_DIR)
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
