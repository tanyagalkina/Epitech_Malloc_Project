##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## @epitech.eu
##

SRC		=	./src/malloc_proj.c 	\
			./src/realloc_proj.c	\
			./src/tools_proj.c	\
			./src/public.c


CFLAGS	=	-Wall -Wextra -Wno-deprecated -g3 -fPIC -I include/

OBJS	=	$(SRC:.c=.o)

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME): $(OBJS)
	gcc -fPIC -shared -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
