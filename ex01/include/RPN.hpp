#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>
# include <stdexcept>
# include <sstream>

class RPN
{
	private:
		bool	isOperator(const std::string& token) const;
		bool	isNumber(const std::string& token) const;
		int		calculus_func(int a, int b, char op) const;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		int		launch_rpn(const std::string& expression) const;
};

#endif
