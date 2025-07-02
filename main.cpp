#include <iostream>
#include "fizzbuzz.h"
#include <cassert>
using namespace std;

bool test01(int vlaue)
{
    assert(fizzBuzz(3) == "Fizz");
    return  true;
}

bool test02(int value)
{
    assert(fizzBuzz(15) == "FizzBuzz");
    return  true;
}

bool test03(int value)
{
    assert(fizzBuzz(7) == "7");
    return  true;
}

    int main()
    {
        int value;
        cin >> value;
       bool a= test01(value);
       if (a) cout << "tes01:1"<<endl;

       bool b=test02(value);
       if (b)cout << "tes02:1" << endl;
     bool c=   test03(value);
     if (c) cout << "tes03:1" << endl;
        cout << fizzBuzz(value) << endl;
        return 0;
    }