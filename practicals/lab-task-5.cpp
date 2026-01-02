#include <iostream>
#include <stack>
#include <string>

using namespace std;

class ExpressionConverter {
private:
    stack<char> st;

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
public:
    string infixToPostfix(const string& infix) {
        string postfix = "";

        for (char c : infix) {
            if (c == ' ') continue;

            if (isalnum(c)) {
                postfix += c;
                postfix += ' ';
            }
            else if (c == '(') {
                st.push(c);
            }
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                if (!st.empty()) st.pop();
            }
            else {
                while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty()) {
            postfix += st.top();
            postfix += ' ';
            st.pop();
        }

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

    cout << "\nPostfix expression: " << postfix << endl;

    return 0;
}
