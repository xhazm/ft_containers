test_stack:
	@c++ -Wall -Wextra -std=c++98 test_stack.cpp
	@./a.out > ft_stack
	@c++ test_stack.cpp -D NS=std
	@./a.out > std_stack
	@diff std_stack ft_stack > diff_stack

test_map:
	@c++ -Wall -Wextra -std=c++98 test_map.cpp
	@./a.out > ft_map
	@c++ test_map.cpp -D NS=std
	@./a.out > std_map
	@diff std_map ft_map > diff_map

