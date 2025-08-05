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


	void TokenizeInput(const string& arrayOfStrings, vector<string>& outParam);

	// i guess this is why you talked abt algorithms cuz of the shunting yard algorithm (goated name btw) 
	// and we're converting to the (RPN - Reverse Polish Notation) (another amazing name)
	void ConvertToRPN(const vector<string>& tokens, vector<string>& rpnOutParam);

	void EvaluateOperation(stack<double>& evalStack, const string& arrayStringOfTokens);

	double EvaluateRPN(const vector<string>& rpn);

	bool IsNumber(const string& token);

	bool IsValidExpression(const vector<string>& tokens);

public:

	/**
 * @brief Processes a mathematical expression and calculates the result.
 *
 * This function takes a line of input representing a mathematical expression,
 * tokenizes it, validates its syntax, converts it to Reverse Polish Notation (RPN),
 * evaluates the RPN expression, and outputs the result.
 *
 * @param line A string representing the mathematical expression to evaluate.
 * @param resultOutParam A reference to a double where the result will be stored
 *        if the expression is valid and evaluation succeeds.
 *
 * @return true if the expression was valid and the result is a finite number,
 *         false otherwise.
 *
 * The function handles the special case of negative zero (-0) and converts it to 0.
 * It does not throw exceptions and assumes internal helper functions handle all
 * parsing and evaluation logic.
 */

	bool ProcessingResult(string line, double& resultOutParam);


};

