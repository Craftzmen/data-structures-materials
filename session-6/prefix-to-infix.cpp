#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

class ExpressionConverter {
private:
    stack<string> st;

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    string stackToString() {
        if (st.empty()) return "(empty)";
        
        stack<string> temp = st;
        string result = "";
        stack<string> reverseStack;
        
        while (!temp.empty()) {
            reverseStack.push(temp.top());
            temp.pop();
        }
        
        while (!reverseStack.empty()) {
            result += reverseStack.top();
            if (reverseStack.size() > 1) result += ", ";
            reverseStack.pop();
        }
        
        return result;
    }

public:
    string prefixToInfix(const string& prefix) {
        string currentInfix = "";
        
        cout << "\n" << left << setw(15) << "Input" 
             << setw(40) << "Stack" 
             << setw(30) << "Infix" << endl;
        cout << string(85, '-') << endl;

        // Read prefix from right to left
        for (int i = prefix.length() - 1; i >= 0; i--) {
            char c = prefix[i];
            
            if (c == ' ') continue;

            // If operand, push to stack
            if (isalnum(c)) {
                st.push(string(1, c));
                currentInfix = string(1, c);
                
                cout << left << setw(15) << string(1, c)
                     << setw(40) << stackToString()
                     << setw(30) << currentInfix << endl;
            }
            // If operator, pop two operands
            else if (isOperator(c)) {
                if (st.size() < 2) {
                    cout << "Error: Invalid prefix expression!" << endl;
                    return "";
                }
                
                string operand1 = st.top(); st.pop();
                string operand2 = st.top(); st.pop();
                
                // Create infix: (operand1 operator operand2)
                currentInfix = "(" + operand1 + c + operand2 + ")";
                st.push(currentInfix);
                
                cout << left << setw(15) << string(1, c)
                     << setw(40) << stackToString()
                     << setw(30) << currentInfix << endl;
            }
        }

        if (st.size() != 1) {
            cout << "Error: Invalid prefix expression!" << endl;
            return "";
        }

        return st.top();
    }
};

int main() {
    string prefix = "";
    char ch;

    cout << "Enter prefix expression character by character\n(press '=' to finish):" << endl;

    while (true) {
        cin >> ch;
        if (ch == '=') break;
        prefix += ch;
    }

    ExpressionConverter converter;
    string infix = converter.prefixToInfix(prefix);

    cout << "\n\nFinal Infix expression: " << infix << endl;

    return 0;
}