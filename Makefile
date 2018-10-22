CC=clang++
FLAGS=-Wall -Wextra -Werror
NAME=avm

INC_DIR=./inc/
SRC_DIR=./src/
OBJ_DIR=./obj/

SRC_NAMES=main.cpp OperandFactory.cpp Application.cpp
SRC=$(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ=$(addprefix $(OBJ_DIR), $(SRC_NAMES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	@grep -xq $(NAME) .gitignore || echo $(NAME) >> .gitignore

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re