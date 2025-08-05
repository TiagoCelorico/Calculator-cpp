#include <iostream>  
#include <sstream>  
#include <string>  
#include <stack>  
#include <vector>  
#include <map>  
#include <cmath>  
#pragma once
using namespace std;

class RPNCalculator
{


	//so that the calc (short for calculator) knows what to do with the operators like the priority abd such	
	int OperatorPrecedence(const string& operation);

	//check it its left to right or right to left, the "^" being the only right associative operator
	bool IsOperatorRightAssociative(const string& powOperation);

	//transform into tokens so that the computer can "read" the numbers and operations while also skipping the white spaces


	void TokenizeInput(const string& arrayOfStrings, vector<string> outParam);

	// i guess this is why you talked abt algorithms cuz of the shunting yard algorithm (goated name btw) 
	// and we're converting to the (RPN - Reverse Polish Notation) (another amazing name)
	void ConvertToRPN(const vector<string>& tokens, vector<string> rpnOutParam);

	void EvaluateOperation(stack<double>& evalStack, const string& arrayStringOfTokens);

	double EvaluateRPN(const vector<string>& rpn);

	bool IsNumber(const string& token);

	bool IsValidExpression(const vector<string>& tokens);

public:
	
	bool ProcessingResult(string line, double& resultOutParam);


};

