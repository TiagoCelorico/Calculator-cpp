
#include <iostream>
#include "RpnCalculator.h"

int main()
{
	RPNCalculator calc;
	
	while (true)
	{
		string line; 
		cout << "Enter an expression: ";
		
		getline(cin, line);

		if (line.empty())
		{
			break;
		}
		
		double result;

		bool success = calc.ProcessingResult(line, result);
		
		if (success) 
		{
			cout << "Result: " << result << "\n";
		}
		else 
		{
			cout << "Invalid mathematical expression.\n";
		}
								
	}

	cout << "Thank you for using the Nelson calculator!!!\n";

	return 0;
}