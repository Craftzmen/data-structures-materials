#include <iostream>
#include <stack>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string postfixToInfix(const string &postfix) {
    stack<string> st;
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        
        if (isalnum(c)) {
            st.push(string(1, c));
        } else if (isOperator(c)) {
            string op2 = st.top();
            st.pop();
            string op1 = st.top();
            st.pop();
            string expr = "(" + op2 + c + op1 + ")";
            st.push(expr);
        }
    }
    return st.top();
}

int main() {
    string postfix = "";
    char ch;

    cout << "Enter postfix expression character by character\n(press '=' to finish):" << endl;

    while (true) {
        cin >> ch;
        if (ch == '=') break;
        postfix += ch;
    }

    string infix = postfixToInfix(postfix);

    cout << "\nInfix expression: " << infix << endl;

    return 0;
}