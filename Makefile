
CONTAINERS	= list vector
INCLUDES	= $(CONTAINERS:%=includes/%.hpp) $(addprefix includes/, DLNode.hpp Color.hpp types.hpp)
TEMPLATE	= $(CONTAINERS:%=templates/%.tpp) $(addprefix templates/, DLNode.tpp)
BINS		= $(CONTAINERS:%=tests/ft::%Test) $(CONTAINERS:%=tests/std::%Test)
MAKE_RESULT	= $(CONTAINERS:%=ft\:\:%) $(CONTAINERS:%=std\:\:%)
SED			= $(CONTAINERS:%=ft\:\:%sed) $(CONTAINERS:%=std\:\:%sed)
RESULTS		= $(CONTAINERS:%=results/ft::%.result) $(CONTAINERS:%=results/std::%.result)
FT_COLORS	= $(CONTAINERS:%=ft\:\:%color)
STD_COLORS	= $(CONTAINERS:%=std\:\:%color)

CC		= clang++
CFLAGS	= -g3 -Wall -Wextra -Werror -Wconversion -std=c++98 -I includes -I templates

all: $(CONTAINERS:%=diff\:\:%)

$(CONTAINERS:%=tests/ft\:\:%Test): tests/ft\:\:%: tests/%.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) tests/$*.cpp -o $@

$(CONTAINERS:%=tests/std\:\:%Test): tests/std\:\:%: tests/%.cpp $(INCLUDES) $(TEMPLATE)
	$(CC) $(CFLAGS) tests/$*.cpp -o $@

$(SED): %sed:
	sed -ri s/"(test_list<).*(>)"/"\1$*\2"/ tests/listTest.cpp

$(MAKE_RESULT): %: %color %sed tests/%Test
	valgrind -q --leak-check=full ./tests/$@Test > results/$@.result

$(MAKE_RESULT:%=show\:\:%): show\:\:%: %
	cat results/$<.result

$(CONTAINERS:%=diff\:\:%): diff\:\:%: std\:\:% ft\:\:%
	@tput setaf 3
	diff -s --unified=0 results/ft::$*.result results/std::$*.result

$(CONTAINERS): %: std\:\:% ft\:\:%
	cat results/ft::$@.result
	@tput setaf 3
	diff -s --unified=0 results/ft::$@.result results/std::$@.result

clean: color
	rm -rf $(BINS)

fclean:	clean
	rm -rf $(RESULTS)

re:	fclean all

$(FT_COLORS):
	@tput setaf 6

$(STD_COLORS):
	@tput setaf 4

color:
	@tput setaf 1

.PHONY:	all clean fclean re $(FT_COLORS) $(STD_COLORS) color