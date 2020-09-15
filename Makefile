
CONTAINERS	= list #Vector
INCLUDES	= $(CONTAINERS:%=includes/%.hpp) $(addprefix includes/, AIterator.hpp DLNode.hpp Color.hpp)
TEMPLATE	= $(CONTAINERS:%=templates/%.tpp) $(addprefix templates/, AIterator.tpp DLNode.tpp)
OBJS		= $(CONTAINERS:%=tests/%Test.o)
BINS		= $(CONTAINERS:%=tests/%Test)
RESULTS		= $(CONTAINERS:%=results/ft::%.result) $(CONTAINERS:%=results/std::%.result)

CC	= clang++
CFLAGS	= -g3 -Wall -Wextra -Werror -Wconversion -std=c++98 -I includes -I templates

all:	$(CONTAINERS)

$(OBJS): %.o: %.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) -c $< -o $@

$(CONTAINERS:%=tests/%Test): %: %.o
	$(CC) $(CFLAGS) $< -o $@

$(CONTAINERS): %: tests/%Test
	valgrind -q --leak-check=full ./$<
	cat results/ft::$@.result
	diff -s --unified=0 results/ft::$@.result results/std::$@.result

clean:
	rm -rf $(OBJS) 

fclean:	clean
	rm -rf $(BINS) $(RESULTS)

re:	fclean all

.PHONY:	all clean fclean re