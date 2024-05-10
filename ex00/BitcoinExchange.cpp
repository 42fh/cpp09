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
	//std::cerr << _daily_rate;
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

	//TODO
	//if date is invalid

	if (c != '|'){
		std::cerr << "Error: invalid format\n";	return ;}

	if (!(amount <= 1000 && amount >= 0)){
			std::cerr << "Error: invalid format\n";	return ;}

	std::cout << date << " => " << amount << " = " << amount * getClosestRate(date) << '\n';
}