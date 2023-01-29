#include <iostream>
#include <windows.h>
#include <conio.h>
#include "needed_functions.h"

using std::string;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

class CommaInputNumber
{
	const long double* number;

public:

	CommaInputNumber()
		:number(new long double(0))
	{
	}

	CommaInputNumber(const long double& number)
		:number(new long double(number))
	{
	}

	CommaInputNumber(const string& input)
		:number(new long double(to_number(input)))
	{
	}

	CommaInputNumber(const CommaInputNumber& obj)
		:number(obj.number)
	{
	}

	CommaInputNumber(CommaInputNumber&& obj) noexcept
		:number(obj.number)
	{
		obj.number = nullptr;
	}

	~CommaInputNumber()
	{
		delete number;
	}

	CommaInputNumber& operator = (const CommaInputNumber& obj)
	{
		if (this == &obj)
			return *this;

		number = obj.number;

		return *this;
	}

	CommaInputNumber& operator = (CommaInputNumber&& obj) noexcept
	{
		if (this == &obj)
			return *this;

		number = obj.number;
		obj.number = nullptr;

		return *this;
	}

	CommaInputNumber operator + (const CommaInputNumber& obj)
	{
		return CommaInputNumber(*number + *obj.number);
	}

	CommaInputNumber operator - (const CommaInputNumber& obj)
	{
		return CommaInputNumber(*number - *obj.number);
	}

	CommaInputNumber operator * (const CommaInputNumber& obj)
	{
		return CommaInputNumber(*number * *obj.number);
	}

	CommaInputNumber operator / (const CommaInputNumber& obj)
	{
		return CommaInputNumber(*number / *obj.number);
	}

	CommaInputNumber operator % (const CommaInputNumber& obj)
	{
		return CommaInputNumber(fmod(*number, *obj.number));
	}

	void change(const string& input)
	{
		number = new long double(to_number(input));
	}

	friend ostream& operator << (ostream& os, const CommaInputNumber& obj)
	{
		return os << *obj.number;
	}
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char input_character = '\0';
	string input_expression("");
	string str_temp_number("");
	CommaInputNumber Number;
	CommaInputNumber TempNumber;

	while (true)
	{
		system("CLS");
		
		cout << "введіть математичний вираз:\n(для закінчення вводу натисність 'enter'/'esc')\n-> ";

		while ((input_character = _getch()) != 27 && input_character != 13)
		{
			if (!is_in(input_character, "\b1234567890/*-+%,"))
				input_character = '\0';

			if (input_character == '\b' && !input_expression.empty())
			{
				input_expression.erase(input_expression.size() - 1);
				system("CLS");
				cout << "введіть математичний вираз:\n(для закінчення вводу натисність 'enter'/'esc')\n-> ";
				cout << input_expression;
				continue;
			}
			
			input_expression += input_character;
			cout << input_character;
		}

		if (find_of("/*-+%", input_expression) == string::npos
			|| find_repeats_of("/*-+%", input_expression)
			|| !isdigit(input_expression[0]) 
			|| !isdigit(input_expression[input_expression.size() - 1]))
		{
			cout << "\nнеправильний ввід!\n";
			input_expression.clear();
			system("PAUSE");
			continue;
		}

		str_temp_number = input_expression.substr(0, find_of("/*-+%", input_expression));

		input_expression.erase(0, find_of("/*-+%", input_expression));
		Number.change(str_temp_number);

		while (!input_expression.empty())
		{
			str_temp_number = input_expression.substr(1, find_of("/*-+%", input_expression.substr(1, input_expression.size() - 1)));
			TempNumber.change(str_temp_number);

			switch (input_expression[0])
			{
			case '+':

				Number = Number + TempNumber;
				break;

			case '-':

				Number = Number - TempNumber;
				break;

			case '*':

				Number = Number * TempNumber;
				break;

			case '/':

				Number = Number / TempNumber;
				break;

			case '%':

				Number = Number % TempNumber;
				break;

			default:
				break;
			}

			input_expression.erase(0, 1);
			input_expression.erase(0, find_of("/*-+%", input_expression));
		}

		input_expression.clear();

		cout << "\nрезультат: " << Number << endl;
		system("PAUSE");
	}
}