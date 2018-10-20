CC=clang++
FLAGS=-Wall -Wextra -Werror
NAME=avm

INC_DIR=./inc/
SRC_DIR=./src/
OBJ_DIR=./obj/

SRC_NAMES=main.cpp
SRC=$(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ=$(addprefix $(OBJ_DIR), $(SRC_NAMES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re $(NAME)
