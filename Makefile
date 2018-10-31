OS=$(shell uname)
CC=clang++
FLAGS=-Wall -Wextra -Werror
NAME=avm

INC_DIR=./inc/
SRC_DIR=./src/
OBJ_DIR=./obj/

HEADER_NAMES=Application.hpp eOperandType.hpp IOperand.hpp OperandFactory.hpp IterStack.hpp Operand.hpp
HEADERS=$(addprefix $(INC_DIR), $(HEADER_NAMES))
SRC_NAMES=main.cpp OperandFactory.cpp Application.cpp
SRC=$(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ=$(addprefix $(OBJ_DIR), $(SRC_NAMES:.cpp=.o))

ifeq ($(OS),Linux)
	BOOST_INC=~/.linuxbrew/include/
	BOOST_LIB=~/.linuxbrew/lib/libboost_regex.a
else
	BOOST_INC=~/.brew/include/
	BOOST_LIB=~/.brew/lib/libboost_regex.a
endif


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(BOOST_LIB)
	@grep -xq $(NAME) .gitignore || echo $(NAME) >> .gitignore
	@echo $(NAME) compiled!

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(FLAGS) $< -o $@ -I $(INC_DIR) -I $(BOOST_INC) -std=c++11

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
