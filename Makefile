.DEFAULT_GOAL		:= all
NAME				= a.out
INCLUDES			= List.hpp
TEMPLATES			= List.tpp
SRCS				= main.cpp
OBJS				= ${SRCS:.cpp=.o}

CC					= clang++
CFLAGS				= -g3 -Wall -Wextra -Werror -Wconversion -std=c++98 -I includes

all:				${NAME}

.cpp.o:
					${CC} ${CFLAGS} -c $< -o $*.o

${OBJS}:			${INCLUDES} ${TEMPLATES}
${NAME}:			${OBJS}
					${CC} ${CFLAGS} $^ -o ${NAME}

clean:
					rm -rf ${OBJS}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all clean fclean re