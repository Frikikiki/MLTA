/*
14.18. Вычисление выражения (7)
Во входной строке записано арифметическое выражение, состоящее из целых чисел и знаков
операций «+», «-», «*», «/», «(», «)», «^». Пробелы в выражении отсутствуют. Требуется написать
программу, которая вычислит значение данного выражения.
Ввод. Входной файл INPUT.TXT содержит одну строку, состоящую не более чем из 255
символов. Числа в выражении не превышают по модулю 2×10 9 . Гарантируется, что в процессе
вычислений получаемые значения не превышают по модулю 2×10 9 .
Вывод. В единственной строке файла OUTPUT.TXT требуется вывести значение выражения с
точностью 4 знака после запятой.
Примеры
Ввод 1          Ввод 2
1+2*3^(1-2/3^4) (1/2+2/3)*(3/4-4/5)*1000
Вывод 1 Вывод 2
6.8394 -58.3333

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>

enum typeOfSymbol { operation, digit, brace_open, brace_close };
enum associativityOfOperation { undefined, left, right };

struct Symbol
{
	char symbol;
	typeOfSymbol type;
	int priority = 0;
	associativityOfOperation associativity = undefined;
	Symbol(const char symbol)
	{
		this->symbol = symbol;
		if ((int)symbol >= 48 && (int)symbol <= 57)
			this->type = digit;
		else if (symbol == '(')
			this->type = brace_open;
		else if (symbol == ')')
			this->type = brace_close;
		else
			this->type = operation;

		if (type == operation)
		{
			if (symbol == '+' || symbol == '-')
				this->priority = 1;
			else if (symbol == '*' || symbol == '/')
				this->priority = 2;
			else if (symbol == '^')
				this->priority = 3;
			if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
				associativity = left;
			else if (symbol == '^')
				associativity = right;
		}
	}
};

std::string InfToPostf(const std::string &str, std::vector<std::string> &numbersStr)
{
	std::string result;
	std::string temp;
	std::stack<Symbol> tempStack;
	std::stack<Symbol> expression;
	std::vector<Symbol> vec;
	for (const char &i : str)
	{
		vec.push_back(Symbol(i));
	}

	for (int i = 0; i < vec.size(); i++)
	{
        if (vec[i].type == digit || ((i == 0 && vec[i].symbol == '-') || 
            (vec[i-1].type == operation && vec[i].symbol == '-') || 
            (vec[i-1].type == brace_open && vec[i].symbol == '-')))
		{
            bool isNegative = false;
            if (vec[i].symbol == '-')
                isNegative = true;
            if (isNegative)
            {
                temp += '-';
                i++;
            }
            while (vec[i].type == digit && i < str.size())
			{
                temp += vec[i].symbol;
				if (vec[i].symbol != '-')
                    result += vec[i].symbol;
				i++;
			}
            if (isNegative)
                result += '~';
			numbersStr.insert(numbersStr.begin(), temp);
			temp = "";
			if (i != vec.size())
				i--;
		}
		else if (vec[i].type == brace_open)
		{
            expression.push(vec[i]);
		}
		else if (vec[i].type == brace_close)
		{
			while (expression.top().type != brace_open)
			{
				result += expression.top().symbol;
				expression.pop();
			}
			expression.pop();
		}
		else
		{
			if (expression.empty() || expression.top().type == brace_open)
				expression.push(vec[i]);
			else if (vec[i].priority > expression.top().priority)
			{
				expression.push(vec[i]);
			}
			else if (vec[i].associativity == left)
			{
				while (expression.top().type != brace_open && !expression.empty())
				{
					if (expression.top().priority >= vec[i].priority)
					{
						result += expression.top().symbol;
						expression.pop();
                        if (expression.empty())
                            break;
					}
					else
					{
						tempStack.push(expression.top());
						expression.pop();
                        if (expression.empty())
                            break;
					}
				}
				while (!tempStack.empty())
				{
					expression.push(tempStack.top());
					tempStack.pop();
				}
				expression.push(vec[i]);
			}
			else if (vec[i].associativity == right)
			{
				expression.push(vec[i]);
			}
		}
	}
	while (!expression.empty())
	{
		result += expression.top().symbol;
		expression.pop();
	}
	return result;
}

double CalculateExpressionByPostf(const std::string &str, std::vector<std::string> &numbersStr)
{
	double result = 0;
	double number1, number2;
	std::string numberStr;
	std::stack<double> numbers;
	for (int i = 0; i < str.size(); i++)
	{
		if ((int)str[i] >= 48 && (int)str[i] <= 57)
		{
			numbers.push(std::stod(numbersStr.back()));
			i += numbersStr.back().size() - 1;
			numbersStr.pop_back();
		}
		else
		{
			number2 = numbers.top();
			numbers.pop();
			number1 = numbers.top();
			numbers.pop();
			if (str[i] == '+')
			{
				numbers.push(number1 + number2);
			}
			else if (str[i] == '-')
			{
				numbers.push(number1 - number2);
			}
			else if (str[i] == '*')
			{
				numbers.push(number1 * number2);
			}
			else if (str[i] == '/')
			{
				numbers.push(number1 / number2);
			}
			else if (str[i] == '^')
			{
				numbers.push(pow(number1, number2));
			}
		}
	}
	return numbers.top();
}

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");
	std::string expression;
	std::getline(inputFile, expression);
	std::vector<std::string> numbersStr;
	std::string exInPostf = InfToPostf(expression, numbersStr);
	outputFile << CalculateExpressionByPostf(exInPostf, numbersStr);
}