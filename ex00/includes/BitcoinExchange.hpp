#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>

class BitcoinExchange
{
private:
	std::map<int, double> _data;

	int			dateToInt(const std::string& date) const;
	bool		isValidDate(const std::string& date, int& year, int& month, int& day) const;
	bool		isValidValue(const std::string& valueStr, double& value) const;
	std::string	trim(const std::string& str) const;
	bool		isLeapYear(int year) const;
	int			getDaysInMonth(int month, int year) const;
	double		getExchangeRate(int dateInt) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void		loadDatabase(const std::string& filename);
	void		processLine(const std::string& line);
};

#endif

