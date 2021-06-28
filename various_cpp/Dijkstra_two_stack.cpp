#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class DijkstraTwoStack {
public:
	using ValType = int;

	DijkstraTwoStack(std::string const& s) {
		size_t i = size_t(-1);

		while (++i < s.size()) {
			if (s[i] == '(')
				continue;
			if (s[i] == ' ')
				continue;

			if (s[i] >= '0' && s[i] <= '9') {
				ValType v = s[i] - '0';
				valueStack_.push(v);
				continue;
			}

			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
				operandStack_.push(s[i]);
				continue;
			}

			if (s[i] == ')') {
				char op = operandStack_.pop();
				ValType v1 = valueStack_.pop();
				ValType v2 = valueStack_.pop();
				ValType res;

				switch (op) {
				case '+': res = v2 + v1; break;
				case '-': res = v2 - v1; break;
				case '*': res = v2 * v1; break;
				case '/': res = v2 / v1; break;
				}

				valueStack_.push(res);
				continue;
			}

			assert(!"Invalid character");
		}

		exprResult = valueStack_.pop();
		std::cout << s << " = " << exprResult << "\n";

		assert(valueStack_.isEmpty());
		assert(operandStack_.isEmpty());
	}

	ValType getResult() const { return exprResult; };

private:
	template<class ValType>
	class Stack {
	public:
		void push(ValType v) {
			stack_.push_back(v);
		}
		
		ValType pop() {
			ValType v = stack_.back();
			stack_.pop_back();
			return v;
		}

		bool isEmpty() const {
			return stack_.empty();
		}

	private:
		std::vector<ValType> stack_;
	};

	Stack<ValType> valueStack_;
	Stack<char> operandStack_;
	ValType exprResult = 0;
};

void test_Dijkstra_two_stack() {
	assert(DijkstraTwoStack("(1+9)").getResult() == 10);
	assert(DijkstraTwoStack("( ((6-4)*2) / (1+3) )").getResult() == 1);
	assert(DijkstraTwoStack("( 1 + ((2*3) * (4*5)) )").getResult() == 121);
}
