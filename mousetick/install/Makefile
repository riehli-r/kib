CC	= gcc
NAME	= install_mousetick
SRC	= install.c

OBJ	= $(SRC:%.c=%.o)
RM	= rm -f
FLAG	= -W -Wall -Werror -ansi -pedantic

$(NAME):	$(OBJ)
		$(CC) $(FLAG) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:			clean
		$(RM) $(NAME)

re:		fclean all
