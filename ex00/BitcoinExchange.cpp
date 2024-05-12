#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string filename)
{
	std::fstream csv(filename.c_str());

	std::string line;
	getline(csv, line);
	if (csv.fail() || line != "date,exchange_rate")
		throw std::runtime_error("first line is not \"date,exchange_rate\"");
	while(getline(csv, line))
	{
		addRate(line);
	}
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::addRate(const std::string line)
{
	std::stringstream ss;
	std::string date;
	double rate;

	ss << line;	
	getline(ss, date, ',');
	ss >> rate;
	if (ss.fail())
		throw std::runtime_error("adding rate for the following line failed:\n" + line);
	addRate(date, rate);
}

double BitcoinExchange::getClosestRate(const std::string& date) const
{
	double ret = 0;

	for(std::map<std::string, double>::const_iterator it = _daily_rate.begin(); it != _daily_rate.end(); ++it)
		{
			if (date > it->first)
				ret = it->second;
			else if (date == it->first)
				return (it->second);
			else if (date < it->first)
				return (ret);
		}
	throw std::runtime_error("map too small");
	return (-1.0);
}

void BitcoinExchange::addRate(const std::string date, const double rate)
{
	_daily_rate.insert(std::pair<std::string, double>(date, rate));
}

void 	BitcoinExchange::evaluate_line(const std::string& line) const
{
	std::stringstream ss;
	std::string date;
	char c;
	double amount;

	ss << line;

	ss >> date;
	ss >> c;
	ss >> amount;

	if (BitcoinExchange::validateDate(date) == false){
		std::cerr << "Error: invalid date\n";	return ;}


	if (c != '|'){
		std::cerr << "Error: invalid format\n";	return ;}

	if (!(amount <= 1000 && amount >= 0)){
			std::cerr << "Error: invalid format\n";	return ;}

	std::cout << date << " => " << amount << " = " << amount * getClosestRate(date) << '\n';
}

static bool leapyear(const int& y)
{
	if (y % 4 == 0 && y % 400 == 0)
		return (true);
	else if (y % 4 == 0 && y % 100 == 0)
		return (false);
	else if (y % 4 == 0)
		return (true);
	else
		return(false);
}

// 3. Januar 2009 is the start date of bitcoin
// we define smallest date as 2009-01-01
bool BitcoinExchange::validateDate(const std::string& date)
{
	if (date.length() != 10)
		return (false);
	if (date.at(4) != '-' or date.at(7) != '-')
		return (false);

	int y;
	int m;
	int d;
	char c1;
	char c2;

	std::stringstream ss;
	ss << date;

	ss >> y;
	ss >> c1;
	ss >> m;
	ss >> c2;
	ss >> d;

//	std::cerr << y << "/" << m << "/" << d << "\n";

	if (ss.fail())
		return (false);

	// reject impossible values
	if (y < 2009 || y > 9999 || m < 1 || m > 12 || d < 1 || d > 31)
		return (false);
	
	// reject impossible days 
	if (m % 2 == 1 && d > 30)
		return (false);

	// special treatment to feb
	if ( (m == 2 && d > 29) || (m == 2 && d == 29 && !leapyear(y)) )
		return (false);

	return (true);
}
