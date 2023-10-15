#include <iostream>
#include <cstring>

class Stack {
private:
    char data[100];
    int top;
public:
    Stack() : top(-1) {}
    void push(char c) {
        data[++top] = c;
    }
    char pop() {
        return data[top--];
    }
    char peek() {
        return data[top];
    }
    bool isEmpty() {
        return top == -1;
    }
};

int getPrecedence(char op) {
    if (op == '|') return 1;
    if (op == '&') return 2;
    if (op == '!') return 3;
    return 0;
}

bool evaluateExpression(const char* expression) {
    Stack operandStack;
    Stack operatorStack;
    int i = 0;
    while (expression[i] != '\0') {
        char ch = expression[i];
        if (ch == ' ') {
            i++;
            continue;
        }
        else if (ch == '(') {
            operatorStack.push(ch);
            i++;
        }
        else if (ch == 'V' || ch == 'F') {
            int t = (ch == 'F' ? 0 : 1);
            while (expression[i] == 'V' || expression[i] == 'F') {
                i++;
            }
            while (!operatorStack.isEmpty() && operatorStack.peek() == '!') {
                t = !t;
                operatorStack.pop();
            }
            operandStack.push(t);
        }
        else if (ch == '|' || ch == '&') {
            while (!operatorStack.isEmpty() && getPrecedence(operatorStack.peek()) >= getPrecedence(ch)) {
                char op2 = operandStack.pop();
                char op1 = operandStack.pop();
                char oper = operatorStack.pop();
                if (oper == '&') {
                    operandStack.push((op1 == 1 && op2 == 1) ? 1 : 0);
                }
                else if (oper == '|') {
                    operandStack.push((op1 == 1 || op2 == 1) ? 1 : 0);
                }
            }
            operatorStack.push(ch);
            i++;
        }
        else if (ch == '!') {
            operatorStack.push(ch);
            i++;
        }
        else if (ch == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                char op2 = operandStack.pop();
                char op1 = operandStack.pop();
                char oper = operatorStack.pop();
                if (oper == '&') {
                    operandStack.push((op1 == 1 && op2 == 1) ? 1 : 0);
                }
                else if (oper == '|') {
                    operandStack.push((op1 == 1 || op2 == 1) ? 1 : 0);
                }
            }
            operatorStack.pop(); 
            while (!operatorStack.isEmpty() && operatorStack.peek() == '!') {
                int t = operandStack.pop();
                operandStack.push(!t);
                operatorStack.pop();
            }
            i++;
        }
    }

    while (!operatorStack.isEmpty()) {
        char op2 = operandStack.pop();
        char op1 = operandStack.pop();
        char oper = operatorStack.pop();
        if (oper == '&') {
            operandStack.push((op1 == 1 && op2 == 1) ? 1 : 0);
        }
        else if (oper == '|') {
            operandStack.push((op1 == 1 || op2 == 1) ? 1 : 0);
        }
    }

    return operandStack.peek() == 1;
}

int main() {
    char expression[101];
    int expressionCount = 0;

    while (std::cin.getline(expression, 101)) {
        ++expressionCount;
        bool result = evaluateExpression(expression);
        std::cout << "Expression " << expressionCount << ": " << (result ? "V" : "F") << std::endl;
    }

    return 0;
}
