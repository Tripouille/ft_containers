#ifndef COLOR_HPP
# define COLOR_HPP
# include <iostream>
# define ENDL RESET << std::endl

enum Color
{
	RED			= 31,
	GREEN		= 32,
	YELLOW 		= 33,
	BLUE		= 34,
	MAGENTA		= 35,
	CYAN		= 36,
	RESET		= 39
};

std::ostream &
operator<<(std::ostream & os, Color c)
{
	return os << "\033[" << static_cast<int>(c) << "m";
}

#endif