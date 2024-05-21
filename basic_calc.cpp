#include <iostream>
#include <stack>
using namespace std;

// a calculator for addition and subtraction only

int main ()
{   
    string s = " 2-1 + 2 ";
    stack<char> st;
    int size = s.length();
    for (int i = 0; i < size; i++) {
                      
        if (s[i] == ')') {
            
            int calculation = 0;
            char left_op = 1;
            stack<char> st2;

            while (st.top() != '(') {
                st2.push(st.top());
                st.pop();
            }

            while (!st2.empty()) {

                char c = st2.top();
                st2.pop();
                
                if (isdigit(c)) {
                    
                    int num = c - '0';
                    while (!st2.empty() && isdigit(st2.top())) {
                        num = num * 10 + st2.top() - '0';
                        st2.pop();
                    }
                    
                    calculation += left_op * num;
                    left_op = 1;
                } else {
                    if (c == '-') {
                        left_op *= -1;
                    }
                }
            }

            st.pop(); // pop '('
            string a = to_string(calculation);

            for (char ch : a) {
                st.push(ch);
            }

        } else if (s[i] != ' ') {

            st.push(s[i]);
        }
    }

    int calculation = 0;
    int left_op = 1;
    stack<char> st2;
    string ans;
    
    while (!st.empty()) {
        
        st2.push(st.top());
        st.pop();
    }

    while (!st2.empty()) {

        char c = st2.top();
        st2.pop();
        ans += c;
    }
    int size2 = ans.length();
    for (int i = 0; i < size2; i++) {

        if (isdigit(ans[i])) {

            int num = ans[i] - '0';  // Convert character to integer

            // If the next character is also a digit, build the complete number
            while (i + 1 < size && isdigit(ans[i + 1])) {
                num = num * 10 + (ans[i + 1] - '0');
                i++;
            }
            calculation += left_op * num;
            left_op = 1;
        } else {
            if (ans[i] == '-') {
                left_op *= -1;
            }
        }
    }
    cout << calculation;

    return 0;
}