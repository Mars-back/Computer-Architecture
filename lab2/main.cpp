#include <iostream>
#include "calculator.h"

using namespace std;

int main()
{
	Calculator calc;

	cout << "3 + 2 = " << calc.Add(3,2) << endl;
	cout << "10 - 2 = " << calc.Sub(10,2) << endl;

	return 0;
}
