#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#define CSV_EX_RATES "data.csv"

class BitcoinExchange
{
private:
	BitcoinExchange();
	BitcoinExchange& operator=(BitcoinExchange& ref);
	void addRate(const std::string line);
	void addRate(const std::string date, const double rate);


	std::map<std::string, double> _daily_rate;

public:
	BitcoinExchange(const std::string filename);
	~BitcoinExchange();

	double	getClosestRate(const std::string& date) const;
	void		evaluate_line(const std::string& line) const;

	static bool validateDate(const std::string& date);
};

/*
std::ostream& operator<<(std::ostream &os, std::map<std::string, double> m)
{
	for(std::map<std::string, double>::iterator it = m.begin(); it != m.end(); ++it)
		{
			os << it->first << ", " << it->second << '\n';
		}
	return(os);
}
*/