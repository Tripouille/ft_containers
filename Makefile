
CONTAINERS	= List #Vector
INCLUDES	= $(CONTAINERS:%=includes/%.hpp)
TEMPLATE	= $(CONTAINERS:%=templates/%.tpp)
SRCS			= $(CONTAINERS:%=tests/%Test.cpp)
OBJS			= $(CONTAINERS:%=tests/%Test.o)
BINS			= $(CONTAINERS:%=tests/%Test)

CC	= clang++
CFLAGS	= -g3 -Wall -Wextra -Werror -Wconversion -std=c++98 -I includes -I templates

all:	$(CONTAINERS)

$(OBJS): %.o: %.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) -c $< -o $@

$(CONTAINERS:%=tests/%Test): %: %.o
	$(CC) $(CFLAGS) $< -o $@

$(CONTAINERS): %: tests/%Test
	valgrind -q --leak-check=full ./$<

clean:
	rm -rf $(OBJS) 

fclean:	clean
	rm -rf $(BINS)

re:	fclean all

.PHONY:	all clean fclean re