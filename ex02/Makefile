#CXX is short for CPP Compiler
CXX:=c++
NAME:=PmergeMe
SRCS:=main.cpp PmergeMe.cpp
OBJS:= ${SRCS:.cpp=.o} 
CPPFLAGS:=-Wall -Wextra -Werror -std=c++98 

all: $(NAME) PmergeMe.hpp

$(NAME): $(OBJS) PmergeMe.hpp
	$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp PmergeMe.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

go: 
	make all
	bash run.sh

21go: 
	make all
	bash run21.sh

ergo: 
	make re
	make go


.PHONY: all clean fclean re go ergo
