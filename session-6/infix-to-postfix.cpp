#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

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

    bool isRightAssociative(char op) {
        return op == '^';
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
    string infixToPostfix(const string& infix) {
        string postfix = "";
        
        cout << "\n" << left << setw(15) << "Input" 
             << setw(15) << "Stack" 
             << setw(30) << "Postfix" << endl;
        cout << string(60, '-') << endl;

        for (char c : infix) {
            if (c == ' ') continue;

            if (isalnum(c)) {
                postfix += c;
                postfix += ' ';
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << postfix << endl;
            }
            else if (c == '(') {
                st.push(c);
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << postfix << endl;
            }
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                if (!st.empty()) st.pop();
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << postfix << endl;
            }
            else {
                while (!st.empty() && st.top() != '(' &&
                       (precedence(st.top()) > precedence(c) ||
                        (precedence(st.top()) == precedence(c) && !isRightAssociative(c)))) {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
                
                cout << left << setw(15) << string(1, c)
                     << setw(15) << stackToString()
                     << setw(30) << postfix << endl;
            }
        }
        
        while (!st.empty()) {
            postfix += st.top();
            postfix += ' ';
            st.pop();
        }
        
        cout << left << setw(15) << "(end)"
             << setw(15) << stackToString()
             << setw(30) << postfix << endl;

        return postfix;
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
    string postfix = converter.infixToPostfix(infix);

    cout << "\n\nFinal Postfix expression: " << postfix << endl;

    return 0;
}
