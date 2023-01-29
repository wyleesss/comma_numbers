#ifndef NEEDED_FUNCTIONS_H
#define NEEDED_FUNCTIONS_H

#include <string>
#include <iostream>

constexpr int power(int number, int power)
{
	int num_copy = number;
	for (int i = 0; i < power; i++)
		number *= num_copy;
	return number;
}

bool is_number(const std::string& str)
{
	if (str.empty())
		return false;

	if (std::count(str.begin(), str.end() - 1, ',') > 1)
		return false;

	for (auto& i : str)
	{
		if (!isdigit(i) && i != ',')
			return false;
	}

	return true;
}

bool is_in(char character, const std::string& str)
{
	for (auto& i : str)
	{
		if (i == character)
			return true;
	}
	return false;
}

size_t find_of(const std::string& find_range, const std::string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		for (auto& j : find_range)
		{
			if (str[i] == j)
				return static_cast<size_t>(i);
		}
	}

	return std::string::npos;
}

bool find_repeats_of(const std::string& find_range, const std::string& str)
{
	for (auto& i : find_range)
	{
		for (int j = 0; j < str.size() - 1; j++)
		{
			if (i == str[j] && i == str[j + 1])
				return true;
		}
	}

	return false;
}

bool is_integer(const long double& number)
{
	return floor(number) == ceil(number);
}

long double to_number(std::string str)
{
	long double number = 0;

	if (!is_number(str))
	{
		std::cout << "(!) неправильний ввід\n(значення встановлено до 0)\n";
		return number;
	}

	number = stoi(str);

	if (str.find(',') == std::string::npos)
		return number;

	str.erase(0, str.find(',') + 1);

	if (str.empty())
		return number;
	
	number += stold(str) / power(10, static_cast<int>(str.size() - 1));
	return number;
}

#endif