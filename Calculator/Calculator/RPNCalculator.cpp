#include "RPNCalculator.h"

inline int RPNCalculator::OperatorPrecedence(const string& operation)
{
	if (operation == "^")					  return 3;
	if (operation == "*" || operation == "/") return 2;
	if (operation == "+" || operation == "-") return 1;

	return 0;
}

inline bool RPNCalculator::IsOperatorRightAssociative(const string& powOperation)
{
	return powOperation == "^";
}

void RPNCalculator::TokenizeInput(const string& arrayOfStrings, vector<string>& outParam)
{



	for (size_t i = 0; i < arrayOfStrings.size();)
	{
		if (isspace(arrayOfStrings[i]))
		{
			continue;
		}
		if ((arrayOfStrings[i] == '-' && i + 1 < arrayOfStrings.size() && isdigit(arrayOfStrings[i + 1])) || isdigit(arrayOfStrings[i]) || arrayOfStrings[i] == '.')
		{
			bool negative = (arrayOfStrings[i] == '-');

			if (negative)
			{
				++i;
			}

			size_t j = i;

			while (j < arrayOfStrings.size() && (isdigit(arrayOfStrings[j]) || arrayOfStrings[j] == '.'))
			{
				++j;
			}

			string number = (negative ? "-" : "") + arrayOfStrings.substr(i, j - i);

			outParam.push_back(number);

			i = j;
			continue;
		}
		else
		{
			// Handle negative sign before parenthesis or at start
			if (arrayOfStrings[i] == '-' && (i == 0 || outParam.empty() || outParam.back() == "(" || (!outParam.empty() && (outParam.back() == "+" || outParam.back() == "-" || outParam.back() == "*" || outParam.back() == "/" || outParam.back() == "^"))))
			{
				outParam.push_back("-1");
				outParam.push_back("*");
				++i;
				continue;
			}

			// Check for implicit multiplication 
			if (arrayOfStrings[i] == '(' && i > 0 && (isdigit(arrayOfStrings[i - 1]) || arrayOfStrings[i - 1] == ')'))
			{
				outParam.push_back("*");
			}

			outParam.push_back(string(1, arrayOfStrings[i]));
			++i;
		}
	}

}

void RPNCalculator::ConvertToRPN(const vector<string>& tokens, vector<string>& rpnOutParam)
{
	stack<string> stack;	// stack to hold operators and parentheses

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		const string& arrayStringOfTokens = tokens[i];

		if (isdigit(arrayStringOfTokens[0]) || (arrayStringOfTokens.size() > 1 && (isdigit(arrayStringOfTokens[1]) || arrayStringOfTokens[0] == '-')))
		{
			rpnOutParam.push_back(arrayStringOfTokens);
			// Check for implicit multiplication after number
			if (i + 1 < tokens.size() && tokens[i + 1] == "(")
			{
				stack.push("*");
			}
			continue;
		}
		if (arrayStringOfTokens == "(")
		{
			stack.push(arrayStringOfTokens);
			continue;
		}
		if (arrayStringOfTokens == ")")
		{
			while (!stack.empty() && stack.top() != "(")
			{
				rpnOutParam.push_back(stack.top());
				stack.pop();
			}
			if (!stack.empty())
			{
				stack.pop();
			}
			// Check for implicit multiplication after closing paren
			if (i + 1 < tokens.size() && (tokens[i + 1] == "(" || isdigit(tokens[i + 1][0]) || (tokens[i + 1].size() > 1 && tokens[i + 1][0] == '-')))
			{
				stack.push("*");
			}
			
			continue;
		}
		else
		{
			while (!stack.empty() && stack.top() != "(" && (OperatorPrecedence(stack.top()) > OperatorPrecedence(arrayStringOfTokens) || (OperatorPrecedence(stack.top()) == OperatorPrecedence(arrayStringOfTokens) && !IsOperatorRightAssociative(arrayStringOfTokens))))
			{
				rpnOutParam.push_back(stack.top());
				stack.pop();
			}
			stack.push(arrayStringOfTokens);
		}
	}
	while (!stack.empty())
	{
		rpnOutParam.push_back(stack.top());
		stack.pop();
	}

}

void RPNCalculator::EvaluateOperation(stack<double>& evalStack, const string& arrayStringOfTokens)
{
	double numberA, numberB;


	numberB = evalStack.top();
	evalStack.pop();
	numberA = evalStack.top();
	evalStack.pop();


	if (arrayStringOfTokens == "+") evalStack.push(numberA + numberB); return;
	if (arrayStringOfTokens == "-") evalStack.push(numberA - numberB); return;
	if (arrayStringOfTokens == "*") evalStack.push(numberA * numberB); return;
	if (arrayStringOfTokens == "/") evalStack.push(numberA / numberB); return;
	if (arrayStringOfTokens == "^") evalStack.push(pow(numberA, numberB)); return;

}

double RPNCalculator::EvaluateRPN(const vector<string>& rpn)
{
	stack<double> evalStack; // stack to hold numbers


	for (const string& arrayStringOfTokens : rpn)
	{
		if (isdigit(arrayStringOfTokens[0]) || (arrayStringOfTokens.size() > 1 && (isdigit(arrayStringOfTokens[1]) || arrayStringOfTokens[0] == '-')))
		{
			evalStack.push(stod(arrayStringOfTokens));
			continue;
		}
		else
		{

			EvaluateOperation(evalStack, arrayStringOfTokens);

		}
	}

	return(evalStack.empty() ? NULL : evalStack.top()); // Return the result or NULL if the stack is empty
}

bool RPNCalculator::IsNumber(const string& token)
{
	if (token.empty()) return false;

	size_t i = 0;
	if (token[0] == '-') ++i; // Negative sign

	bool hasDigits = false;
	bool hasDecimal = false;

	for (; i < token.size(); ++i)
	{
		if (isdigit(token[i]))
		{
			hasDigits = true;
			continue;
		}
		if (token[i] == '.')
		{
			if (hasDecimal) return false; // Second dot not allowed
			hasDecimal = true;
			continue;
		}
		else
		{
			return false; // Invalid character
		}
	}

	return hasDigits;
}

inline bool RPNCalculator::IsValidExpression(const vector<string>& tokens)
{
	int parentheses = 0;
	bool lastWasOperator = true;

	for (const string& token : tokens)
	{
		if (token == "(")
		{
			parentheses++;
			lastWasOperator = true;
			continue;
		}
		if (token == ")")
		{
			parentheses--;
			if (parentheses < 0) return false;
			lastWasOperator = false;
			continue;
		}
		if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
		{
			if (lastWasOperator) return false; // Two operators in a row
			lastWasOperator = true;
			continue;
		}
		if (IsNumber(token))
		{
			lastWasOperator = false;
			continue;
		}
		else
		{
			return false; // Not a number, not an operator, not a parenthesis
		}
	}

	return parentheses == 0 && !lastWasOperator;
}


bool RPNCalculator::ProcessingResult(string line, double& resultOutParam)
{
	vector<string> tokens;

	TokenizeInput(line, tokens);

	if (!IsValidExpression(tokens))
	{

		return 0;
	}

	vector<string> rpn;

	ConvertToRPN(tokens, rpn);

	resultOutParam = EvaluateRPN(rpn);

	if (resultOutParam == -0)
	{
		resultOutParam = 0; // Handle -0 case
	}

	return isfinite(resultOutParam);
}
