#include "BitcoinExchange.hpp"

static void 	process_date_list(std::string filename, const BitcoinExchange& ex)
{
	std::fstream fs(filename.c_str());
	if (fs.fail()){
		std::cerr << "Error: could not open file.\n"; return ;}

	std::string line;
	while(getline(fs, line))
		{
			ex.evaluate_line(line);
		}
	
}


// takes a file as argument
// file format:
/*Each line in this file must use the following format: "date | value".
A valid date will always be in the following format: Year-Month-Day.
A valid value must be either a float or a positive integer, between 0 and 1000 */
// prg: read in file, store in map, 
// evaluate a single pair
// evaluate in a list
int main(int ac, const char *av[])
{
	(void) av;
	if (ac != 2){
		std::cerr << "Error: could not open file.\n"; return (1);}

	BitcoinExchange ex(CSV_EX_RATES);


	process_date_list(av[1], ex);
	
	
	//std::cerr <<	ex.getClosestRate("2022-03-26") << '\n';
	
	return (0);
}