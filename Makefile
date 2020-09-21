
CONTAINERS	= list #Vector
INCLUDES	= $(CONTAINERS:%=includes/%.hpp) $(addprefix includes/, DLNode.hpp Color.hpp types.hpp)
TEMPLATE	= $(CONTAINERS:%=templates/%.tpp) $(addprefix templates/, DLNode.tpp)
BINS		= $(CONTAINERS:%=tests/ft::%Test) $(CONTAINERS:%=tests/std::%Test)
MAKE_RESULT	= $(CONTAINERS:%=ft\:\:%) $(CONTAINERS:%=std\:\:%)
SED			= $(CONTAINERS:%=ft\:\:%sed) $(CONTAINERS:%=std\:\:%sed)
RESULTS		= $(CONTAINERS:%=results/ft::%.result) $(CONTAINERS:%=results/std::%.result)

CC		= clang++
CFLAGS	= -g3 -Wall -Wextra -Werror -Wconversion -std=c++98 -I includes -I templates

all: $(CONTAINERS:%=diff\:\:%)

$(CONTAINERS:%=tests/ft\:\:%Test): tests/ft\:\:%: tests/%.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) tests/$*.cpp -o $@

$(CONTAINERS:%=tests/std\:\:%Test): tests/std\:\:%: tests/%.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) tests/$*.cpp -o $@

$(SED): %sed:
	sed -ri s/"(test_list<).*(>)"/"\1$*\2"/ tests/listTest.cpp

$(MAKE_RESULT): %: color %sed tests/%Test
	valgrind -q --leak-check=full ./tests/$@Test > results/$@.result

$(MAKE_RESULT:%=show\:\:%): show\:\:%: %
	cat results/$<.result

$(CONTAINERS:%=diff\:\:%): diff\:\:%: ft\:\:% std\:\:%
	diff -s --unified=0 results/ft::$*.result results/std::$*.result

$(CONTAINERS): %: ft\:\:% std\:\:%
	cat results/ft::$@.result
	diff -s --unified=0 results/ft::$@.result results/std::$@.result

clean: color
	rm -rf $(BINS)

fclean:	clean
	rm -rf $(RESULTS)

re:	fclean all

color:
	@tput setaf 6

.PHONY:	all clean fclean re color