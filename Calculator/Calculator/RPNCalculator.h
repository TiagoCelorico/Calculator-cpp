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


private:
	
	int OperatorPrecedence(const string& operation);

	bool IsOperatorRightAssociative(const string& powOperation);

	void TokenizeInput(const string& arrayOfStrings, vector<string>& outParam);

	void ConvertToRPN(const vector<string>& tokens, vector<string>& rpnOutParam);

	void EvaluateOperation(stack<double>& evalStack, const string& arrayStringOfTokens);

	double EvaluateRPN(const vector<string>& rpn);

	bool IsNumber(const string& token);

	bool IsValidExpression(const vector<string>& tokens);



};

