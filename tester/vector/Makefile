NAME	= ft_containers

SRC_DIR	= ./
SRC		= vector_test_main.cpp


OBJ_DIR	= obj/
OBJ		= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

all : $(OBJ_DIR) $(NAME) $(HDR)

$(NAME) : $(OBJ) $(HDR)
	c++ $(FLAGS) $(OBJ) -g -o $(NAME)

$(OBJ_DIR)%.o :$(SRC_DIR)%.cpp $(HDR)
	c++ $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir obj

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all