#include <string>
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

bool char2bool(char statement);
char bool2char(bool statement);
bool check(char symbol);
int priority(char symbol);

int evaluate(string infix, string& postfix, bool& result) {
	while (!postfix.empty())
		postfix.pop_back();
	stack<char> opStack;
	char prevsymbol = ' ';
	/*organization of infix*/
	for (size_t i = 0; i < infix.length(); i++) {
		switch (infix[i])
		{
		case ' ':
			continue;
		//operand
		case 'T':
		case 'F':
			if (check(prevsymbol))
				return 1;
			postfix += infix[i];
			break;
		//parentheses
		case '(':
			if (check(prevsymbol))
				return 1;
			opStack.push(infix[i]);
			break;
		case ')':
			if (!check(prevsymbol))
				return 1;
			while (!opStack.empty() && opStack.top() != '(') {
				postfix += opStack.top();
				opStack.pop();
			}
			if (opStack.empty())
				return 1;
			opStack.pop();
			break;

		//operators
		case '!':
			if (check(prevsymbol))
				return 1;
			opStack.push('!');
			break;

		case '&':
		case '|':
			if (!check(prevsymbol))
				return 1;
			while (!opStack.empty() && priority(infix[i])<=priority(opStack.top())) {
				postfix += opStack.top();
				opStack.pop();
			}
			opStack.push(infix[i]);
			break;

		default:
			return 1;
		}
		prevsymbol = infix[i];
	} 
	if (!check(prevsymbol))
		return 1;
	while (!opStack.empty()) {
		postfix += opStack.top();
		opStack.pop();
	}/*conversion to postfix complete*/

	/*execute postfix*/
	string temp;
	bool para1;
	bool para2;
	for (int i = 0; i < (int)postfix.length(); i++) {
		switch (postfix[i]) {
		case 'T':
		case 'F':
			temp.push_back(postfix[i]);
			break;
		case '|':
			if (temp.length() >= 2) {
				para1 = char2bool(temp[temp.length() - 2]);
				para2 = char2bool(temp[temp.length() - 1]);
				temp.pop_back();
				temp.pop_back();
				temp.push_back(bool2char(para1 || para2));
				break;
			}
			else
				return 1;
		case '&':
			if (temp.length() >= 2) {
				para1 = char2bool(temp[temp.length() - 2]);
				para2 = char2bool(temp[temp.length() - 1]);
				temp.pop_back();
				temp.pop_back();
				temp.push_back(bool2char(para1 && para2));
				break;
			}
			else
				return 1;
		case '!':
			if (temp.length() >= 1) {
				para1 = char2bool(temp[temp.length() - 1]);
				temp.pop_back();
				temp.push_back(bool2char(!para1));
				break;
			}
			else
				return 1;
		default:
			return 1;
		}
	}
	if (temp.length() == 1) {
		result = char2bool(temp[0]);
		return 0;
	}
	else
		return 1;
}
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

bool char2bool(char statement) {
	assert(statement == 'F' || statement == 'T');
	switch (statement) {
	case 'T':
		return true;
	case 'F':
		return false;
	default:
		return false;
	}
}

char bool2char(bool statement) {
	switch (statement) {
	case true:
		return 'T';
	case false:
		return 'F';
	}
}

bool check(char symbol) {
	return (symbol == 'T' || symbol == 'F' || symbol == ')');
}

int priority(char symbol) {
	assert(symbol == '!' || symbol == '&' ||
		symbol == '|' || symbol == '(');
	switch (symbol) {
	case '!':
		return 4;
	case '&':
		return 3;
	case '|':
		return 2;
	case '(':
		return 1;
	default:
		return -1;
	}
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	cout << "Passed all tests" << endl;
}