#include "fizzbuzz.h"
#include <iostream>

using namespace std;

std::string fizzBuzz(int value)
{
	if (value % 3 == 0 && value % 5 == 0)
	{
		return "FizzBuzz";
	}
	else if (value % 5 == 0)
	{
		return "Buzz";
	}
	else if (value % 3 != 0 && value % 5 != 0)
	{
		return to_string(value);
	}
	else if (value % 3 == 0)
	{
		return "Fizz";
	}
}