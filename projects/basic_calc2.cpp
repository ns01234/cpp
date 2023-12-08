#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main ()
{   
    string s = "14/7+3";
    stack<char> st;
    string w;
    for (auto c : s) {
        if (c != ' ')
            w += c;
    }
    int left_number = 1;
    int size = w.length();
    int ans = 0;
    int d = 0;
    for (int i = 0; i < size; i++) {

        if (isdigit(w[i])) {
            
            d = 0;
            long long num = w[i] - '0';
            while (i < size - 1 && isdigit(w[i+1])) {
                num = num * 10 + (w[i+1] - '0');
                i++;
            }
            string s_num = to_string(num);
            left_number = num;
            for (auto digit : s_num) {
                st.push(digit);
                d++;
            }
            
        } else if (w[i] == '*') {
            
            for (int i = 0; i < d; i++)
                st.pop();
            d = 0;
            long long num = w[i+1] - '0';
            i++;
            while (i < size - 1 && isdigit(w[i+1])) {
                num = num * 10 + (w[i+1] - '0');
                i++;
            }

            string s_num = to_string(left_number * num);
            left_number = left_number * num;
            for (auto digit : s_num) {
                st.push(digit);
                d++;
            }
        } else if (w[i] == '/') {
            
            for (int i = 0; i < d; i++)
                st.pop();
            d = 0;
            long long num = w[i+1] - '0';
            i++;
            while (i < size - 1 && isdigit(w[i+1])) {
                num = num * 10 + (w[i+1] - '0');
                i++;
            }

            string s_num = to_string(left_number / num);
            left_number = left_number / num;
            for (auto digit : s_num) {
                st.push(digit);
                d++;
            }
        } else {

            st.push(w[i]);
        }
    }

    stack<char> st2;
    left_number = 1;
    while (!st.empty()) {
        st2.push(st.top());
        st.pop();
    }

    while (!st2.empty()) {

        if (isdigit(st2.top())) {
            
            long long num = st2.top() - '0';
            st2.pop();
            while (st2.size() > 0 && isdigit(st2.top())) {
                num = num * 10 + (st2.top() - '0');
                st2.pop();
            }

            ans += left_number * num;
            left_number = 1;

        } else {
            if (st2.top() == '-') {
                left_number = -1;
            }
            st2.pop();
        }
    }

    return 0;
}