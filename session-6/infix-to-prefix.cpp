#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class ExpressionConverter {
private:
    stack<char> st;

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    string stackToString() {
        if (st.empty()) return "(empty)";
        
        stack<char> temp = st;
        string result = "";
        
        while (!temp.empty()) {
            result = temp.top() + result;
            temp.pop();
        }
        return result;
    }

public:
    string infixToPrefix(const string& infix) {
        // Step 1: Reverse the infix expression
        string reversedInfix = infix;
        reverse(reversedInfix.begin(), reversedInfix.end());
        
        // Step 2: Replace '(' with ')' and vice versa
        for (int i = 0; i < reversedInfix.length(); i++) {
            if (reversedInfix[i] == '(') reversedInfix[i] = ')';
            else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
        }
        
        string prefix = "";
        
        cout << "\n" << left << setw(15) << "Input" 
             << setw(15) << "Stack" 
             << setw(30) << "Prefix (reversed)" << endl;
        cout << string(60, '-') << endl;

        // Step 3: Convert to postfix with modified associativity
        for (char c : reversedInfix) {
            if (c == ' ') continue;

            if (isalnum(c)) {
                prefix += c;
                prefix += ' ';
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << prefix << endl;
            }
            else if (c == '(') {
                st.push(c);
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << prefix << endl;
            }
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    prefix += st.top();
                    prefix += ' ';
                    st.pop();
                }
                if (!st.empty()) st.pop();
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << prefix << endl;
            }
            else {
                // For prefix: pop when stack top has GREATER precedence
                // OR when precedence is EQUAL and operator is NOT ^
                while (!st.empty() && st.top() != '(' &&
                       (precedence(st.top()) > precedence(c) ||
                        (precedence(st.top()) == precedence(c) && c != '^'))) {
                    prefix += st.top();
                    prefix += ' ';
                    st.pop();
                }
                st.push(c);
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << prefix << endl;
            }
        }
        
        while (!st.empty()) {
            prefix += st.top();
            prefix += ' ';
            st.pop();
        }
        
        cout << left << setw(15) << "(end)"
             << setw(15) << stackToString()
             << setw(30) << prefix << endl;

        // Step 4: Reverse the result to get prefix
        reverse(prefix.begin(), prefix.end());
        
        return prefix;
    }
};

int main() {
    string infix = "";
    char ch;

    cout << "Enter infix expression character by character\n(press '=' to finish):" << endl;

    while (true) {
        cin >> ch;
        if (ch == '=') break;
        infix += ch;
    }

    ExpressionConverter converter;
    string prefix = converter.infixToPrefix(infix);

    cout << "\n\nFinal Prefix expression: " << prefix << endl;

    return 0;
}