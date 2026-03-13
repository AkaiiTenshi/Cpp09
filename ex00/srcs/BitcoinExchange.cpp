#include "BitcoinExchange.hpp"

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string BitcoinExchange::trim(const std::string& str) const
{
	size_t start = 0;
	size_t end = str.length();

	while (start < end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r'))
		start++;

	while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\n' || str[end - 1] == '\r'))
		end--;

	return str.substr(start, end - start);
}

bool BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::getDaysInMonth(int month, int year) const
{
	if (month == 2)
		return isLeapYear(year) ? 29 : 28;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	return 31;
}

int BitcoinExchange::dateToInt(const std::string& date) const
{
	int year, month, day;

	if (!isValidDate(date, year, month, day))
		return -1;

	return year * 10000 + month * 100 + day;
}

bool BitcoinExchange::isValidDate(const std::string& date, int& year, int& month, int& day) const
{
	if (date.length() != 10)
		return false;

	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	std::stringstream ssYear(yearStr);
	std::stringstream ssMonth(monthStr);
	std::stringstream ssDay(dayStr);
	
	ssYear >> year;
	ssMonth >> month;
	ssDay >> day;

	// Validate ranges
	if (year < 1000 || year > 9999)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > getDaysInMonth(month, year))
		return false;

	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const
{
	std::stringstream ss(valueStr);
	ss >> value;

	if (ss.fail() || !ss.eof())
		return false;

	return true;
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("could not open database file.");
	}

	std::string line;
	bool firstLine = true;

	while (std::getline(file, line))
	{
		if (firstLine)
		{
			firstLine = false;
			continue;
		}

		if (line.empty())
			continue;

		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;

		std::string dateStr = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1);

		int dateInt = dateToInt(dateStr);
		if (dateInt == -1)
			continue;

		double rate;
		std::stringstream ss(rateStr);
		ss >> rate;

		_data[dateInt] = rate;
	}

	file.close();
}

double BitcoinExchange::getExchangeRate(int dateInt) const
{
	std::map<int, double>::const_iterator it = _data.lower_bound(dateInt);

	if (it != _data.end() && it->first == dateInt)
		return it->second;

	if (it == _data.begin())
		return -1; 

	--it;
	return it->second;
}

void BitcoinExchange::processLine(const std::string& line)
{
	if (trim(line).empty())
		return;

	size_t pipePos = line.find(" | ");
	if (pipePos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string dateStr = trim(line.substr(0, pipePos));
	std::string valueStr = trim(line.substr(pipePos + 3));

	int year, month, day;
	if (!isValidDate(dateStr, year, month, day))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	int dateInt = year * 10000 + month * 100 + day;

	double value;
	if (!isValidValue(valueStr, value))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}

	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	double rate = getExchangeRate(dateInt);
	if (rate < 0)
	{
		std::cout << "Error: bad input => " << dateStr << std::endl;
		return;
	}

	double result = value * rate;

	std::cout << dateStr << " => " << value << " = " << result << std::endl;
}
