##
## Makefile for Makefile in /home/durand_u/github/Myirc
## 
## Made by Rémi DURAND
## Login   <durand_u@epitech.net>
## 
## Started on  Mon Apr  6 12:44:38 2015 Rémi DURAND
## Last update Sat Apr 11 13:38:13 2015 Ambroise Coutarel
##

SRC_SERVER	=	./server_dir/irc.c			\
			./server_dir/init.c			\
			./server_dir/client_handler.c		\
			./server_dir/my_str_to_wordtab.c	\
			./server_dir/cmds_handler.c		\
			./server_dir/cmds.c			\
			./server_dir/cmds2.c			\
			./server_dir/cmds3.c

SRC_CLIENT	=	./client_dir/main_client.c		\
			./client_dir/client_cmds.c		\
			./client_dir/my_str_to_wordtab.c	\
			./client_dir/cmd_parsing.c

CC		=	gcc

RM		=	rm -f

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	server

NAME_CLIENT	=	client

CFLAGS		+=	-Wall -Wextra -Werror -g3

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS)

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all
