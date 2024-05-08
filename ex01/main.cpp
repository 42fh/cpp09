// $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// $> ./RPN "7 7 * 7 -"
// 42
// $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
// 0
// $> ./RPN "(1 + 1)"
// Error
// $>

// maps char --> int
// eg 1 2 + becomes 3
// 1 2 3 * + becomes 7
// 1 2 + 3 * => 9

// now that I'm implementing the for loop i notice that I want to have both numbers (as the result ) and chars 
// upon realizing 

#include "RPN.hpp"

int main(int argc, char const *argv[])
{
	if (argc not_eq 2)
		::std::cerr << "error: provide exactly one arg, eg:\n./RPN \"7 7 * 7 -\"\n";
	else
	{
		try
		{
			RPN instance(argv[1]);
			std::cout << instance.calc() << '\n';
		}
		catch(const std::exception& e)
		{
			// std::cerr << e.what() << '\n';
			std::cerr << "Error\n";
		}		
	}
	return 0;
}
