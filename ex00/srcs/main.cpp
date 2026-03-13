#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange btc;

		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			std::cerr << "Error: could not open file." << std::endl;
			return 1;
		}

		std::string line;
		bool firstLine = true;

		while (std::getline(inputFile, line))
		{
			// Skip header line (first line)
			if (firstLine)
			{
				firstLine = false;
				continue;
			}

			btc.processLine(line);
		}

		inputFile.close();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
