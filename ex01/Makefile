#CXX is short for CPP Compiler
CXX:=c++
NAME:=RPN
SRCS:=main.cpp RPN.cpp
OBJS:= ${SRCS:.cpp=.o} 
CPPFLAGS:=-Wall -Wextra -Werror -std=c++98 

all: $(NAME) RPN.hpp

$(NAME): $(OBJS) RPN.hpp
	$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

go: 
	make all
	./$(NAME)

ergo: 
	make re
	./$(NAME)


.PHONY: all clean fclean re go ergo
