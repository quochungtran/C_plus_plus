// Stack : LIFO (last in first out)
// stack<data_type> variable
#include <stack>
#include <iostream>

using namespace std;

void print_stack(stack<int>& st)
{
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main()
{
    stack<int> st;
    st.push(5);
    st.push(7);
    st.push(3);

    stack<int> st2;
    st2.push(4);
    st2.push(5);
    st2.push(6);


    st.swap(st2);

    cout << "After swap : " << endl;
    cout << "stack 1 : ";
    print_stack(st);
    cout << "stack 2 : ";
    print_stack(st2);

    return 0;
}