##
## Makefile for Makefile in /home/durand_u/github/Myirc
## 
## Made by Rémi DURAND
## Login   <durand_u@epitech.net>
## 
## Started on  Mon Apr  6 12:44:38 2015 Rémi DURAND
## Last update Wed Apr  8 15:45:47 2015 Ambroise Coutarel
##

SRC_SERVER      =       ./server_dir/irc.c                   \
			./server_dir/init.c                   \
			./server_dir/client_handler.c

#SRC_CLIENT      =

CC              =       gcc

RM              =       rm -f

OBJ_SERVER      =       $(SRC_SERVER:.c=.o)

#OBJ_CLIENT      =       $(SRC_CLIENT:.c=.o)

NAME_SERVER     =       server

#NAME_CLIENT     =       client

CFLAGS          +=      -Wall -Wextra -Werror -g3

all: $(NAME_SERVER)# $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS)

#$(NAME_CLIENT): $(OBJ_CLIENT)
#	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS)

clean:
	$(RM) $(OBJ_SERVER) 
# $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER) 
# $(NAME_CLIENT)

re: fclean all
