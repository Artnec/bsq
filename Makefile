NAME		=	bsq

CC			=	clang

FLAGS		=	-O2 -Wall -Werror -Wextra

SRC			=	main.c	read_and_save_map.c	solve.c

INC			=	bsq.h

HEADER		=	$(addprefix $(SRC_DIR), $(INC))

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC_DIR		=	src/
OBJ_DIR		=	obj/


all: $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
