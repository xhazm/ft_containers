NAME	= ft_containers

SRC_DIR	= ./
SRC		= avl_main.cpp 

HDR	=  ./inc/vector.hpp

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

valgrind: re
	rm -f valgrind.log
	G_SLICE=always-malloc G_DEBUG=gc-friendly  valgrind -v --tool=memcheck --leak-check=full --num-callers=40 --log-file=valgrind.log /home/sirlin/code/ft_containers/ft_containers
	tail -1 ./valgrind.log